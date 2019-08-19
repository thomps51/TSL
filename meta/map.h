#pragma once

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 18 August 2019

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::meta::map

#include <type_traits>

// Naive implementation of compile type value to type map.

namespace tsl { namespace meta {
   
   /* @brief
      Type/value pair. Create using make_pair().
    */
   template <class KeyType, class ValueType>
   struct pair;

   /* @brief
      Returns type/value pair. Used within make_map().
    */
   template <class ValueType, class KeyType>
   constexpr pair<KeyType, ValueType>
   make_pair(KeyType _key);

   template <class...>
   struct answer
   {
      constexpr answer(int _index)
         : index(_index)
      {}

      int index;
   };

   /* @brief
      Container mapping values to types, the simple example being string literals to types, such as
      "int" to int.  Values do not all have to be of the same type. Create using make_map() as shown
      below. Search for types by value using TSL_META_FIND_TYPE as shown below:

      @code
      auto constexpr my_map = make_map(
         make_pair<int>("int")
         , make_pair<double>("double")
         , make_pair<unsigned>(1)
         , make_pair<my_type>("my_type")
         , make_pair<long>("long"));

      static_assert(std::is_same_v<int,      TSL_META_FIND_TYPE(my_map, "int")>);
      static_assert(std::is_same_v<double,   TSL_META_FIND_TYPE(my_map, "double")>);
      static_assert(std::is_same_v<long,     TSL_META_FIND_TYPE(my_map, "long")>);
      static_assert(std::is_same_v<my_type,  TSL_META_FIND_TYPE(my_map, "my_type")>);
      static_assert(std::is_same_v<unsigned, TSL_META_FIND_TYPE(my_map, 1)>);
      @endcode

      You can also enumerate all types stored in the map by calling map::enumerate():
      @code
      auto constexpr my_map = make_map(
         make_pair<int>("int")
         , make_pair<double>("double")
         , make_pair<unsigned>(1)
         , make_pair<my_type>("my_type")
         , make_pair<long>("long"));

      struct my_handler
      {
         template <class KeyType, class ValueType>
         void
         on_value(ValueType _value)
         {
            // ... logic here
         }
      };

      my_handler handler;
      my_map.enumerate(handler); // calls handler<ValueType>(KeyType) for each pair in map.

      @end

      @note Types and values are assumed to be unique.
    */
   template <class...>
   class map;

   // base case
   template <class Pair>
   class map<Pair>
   {
   public:
      constexpr map(Pair _arg);

      template <class Enumerator>
      constexpr void
      enumerate(Enumerator & _handler) const;
      
      template <class KeyType>
      constexpr answer<Pair>
      find(KeyType _key) const;
      
      template <class ValueType>
      constexpr answer<Pair>
      find() const;

   private:
      Pair current;
   };
  
   // recursive case
   template <class Pair, class... Pairs>
   struct map<Pair, Pairs...>
   {
      constexpr map(Pair _arg, Pairs... _args);

      template <class Enumerator>
      constexpr void
      enumerate(Enumerator & _handler) const;

      template <class KeyType>
      constexpr answer<Pair, Pairs...>
      find(KeyType _key) const;

      template <class ValueType>
      constexpr answer<Pair, Pairs...>
      find() const;

      Pair          current;
      map<Pairs...> others;
   };

   template <class... Args>
   constexpr map<Args...>
   make_map(Args... _args);

#define TSL_META_FIND_TYPE(_map, _key)                                                             \
   typename tsl::meta::details::extract_type<_map.find(_key).index, decltype(_map)>::type
}}

namespace tsl { namespace meta { namespace details {
   // shamelessly stolen from std::tuple_element cppreference page.
   template <std::size_t I, class T>
   struct extract_type;

   // recursive case
   template <std::size_t I, class Head, class... Tail>
   struct extract_type<I, const map<Head, Tail...>> : extract_type<I - 1, const map<Tail...>>
   {
   };

   // base case
   template <class Head, class... Tail>
   struct extract_type<0, const map<Head, Tail...>>
   {
      using type = typename Head::value;
   };

   // **********************************************************************************************
   // Notes: For string literals we want to make sure to compare them properly, so we turn them and
   // any other string like objects into string_views.
   // ----------------------------------------------------------------------------------------------
   template <class LhsType, class RhsType>
   constexpr bool
   compare(LhsType _lhs, RhsType _rhs)
   {
      bool result(false);
      if constexpr(std::is_same_v<LhsType, RhsType>)
      {
         if constexpr(std::is_constructible_v<std::string_view, LhsType>)
         {
            result = std::string_view(_lhs) == std::string_view(_rhs);
         }
         else
         {
            result = _lhs == _rhs;
         }
      }
      return result;
   }
}}}

namespace tsl { namespace meta {
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class KeyType, class ValueType>
   struct pair
   {
      using value = ValueType;
      KeyType key;
      constexpr pair(KeyType _key)
         : key(_key)
      {
      }
   };

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class... Args>
   constexpr map<Args...>
   make_map(Args... _args)
   {
      return map<Args...>(_args...);
   }

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class ValueType, class KeyType>
   constexpr pair<KeyType, ValueType>
   make_pair(KeyType _key)
   {
      return pair<KeyType, ValueType>(_key);
   }
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class Pair>
   constexpr
   map<Pair>::map(Pair _arg)
      : current(_arg)
   {
   }
   
   template <class T, class KeyType, class ValueType, class = void>
   struct is_valid_enumerator : std::false_type
   {

   };

   template <class T, class KeyType, class ValueType>
   struct is_valid_enumerator<T, KeyType, ValueType,
      std::void_t<decltype(
         std::declval<T>().template on_value<ValueType>(std::declval<KeyType>()))>> : std::true_type
   {
   };

   template <class T, class KeyType, class ValueType>
   inline constexpr bool is_valid_enumerator_v = is_valid_enumerator<T, KeyType, ValueType>::value;
   
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class Pair>
   template <class Enumerator>
   constexpr void
   map<Pair>::enumerate(Enumerator & _handler) const
   {
      static_assert(is_valid_enumerator_v<Enumerator, decltype(current.key), typename Pair::value>);
      _handler.template on_value<typename Pair::value>(current.key);
   }

   // **********************************************************************************************
   // Notes: We will only use this in a constexpr context, so throwing an exception will be similar
   // to triggering a static_assert.  We have no way to trigger a static assert here because the
   // comparison depends on _key.  This is where we would want a "consteval" function so that we
   // don't have to make this work at runtime as well.
   // ----------------------------------------------------------------------------------------------
   template <class Pair>
   template <class KeyType>
   constexpr answer<Pair>
   map<Pair>::find(KeyType _key) const
   {
      decltype(find(_key)) result(0);
      if (!details::compare(_key, current.key))
      {
         throw "Key not found in map";
      }
      return result;
   }
   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class Pair, class... Pairs>
   constexpr
   map<Pair, Pairs...>::map(Pair _arg, Pairs... _args)
      : current(_arg)
      , others(_args...)
   {
   }

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class Pair, class... Pairs>
   template <class Enumerator>
   constexpr void
   map<Pair, Pairs...>::enumerate(Enumerator & _handler) const
   {
      static_assert(is_valid_enumerator_v<Enumerator, decltype(current.key), typename Pair::value>);
      _handler.template on_value<typename Pair::value>(current.key);
      others.enumerate(_handler);
   }

   // **********************************************************************************************
   // Notes:
   // ----------------------------------------------------------------------------------------------
   template <class Pair, class... Pairs>
   template <class KeyType>
   constexpr answer<Pair, Pairs...>
   map<Pair, Pairs...>::find(KeyType _key) const
   {
      bool const found(details::compare(_key, current.key));
      if (found)
      {
         decltype(find(_key)) result(0);
         return result;
      }
      auto retval(others.find(_key));
      decltype(find(_key)) result(retval.index + 1);
      return result;
   }
}}
