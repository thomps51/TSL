#pragma once
#ifndef included_tsl_utility_buffer_08July2018_
#define included_tsl_utility_buffer_08July2018_

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 08 July 2018

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::utility::buffer

#include <algorithm>
#include <cstddef>
#include <string>
#include <type_traits>


namespace tsl::utility
{
    template <class T, class SizeType = size_t>
    class buffer
    {
    public:
        buffer(SizeType _capacity);

        ~buffer();

        void
        append(T const * _data, SizeType _size);

        void
        clear();
        
        SizeType
        capacity();

        T *
        data();

        SizeType
        size();

        typename std::enable_if<std::is_same<T, char>::value, std::string>::type
        as_string();

        typename std::enable_if<std::is_same<T, char>::value, std::string_view>::type
        as_view();

    private:
        SizeType capacity_;
        T *      data_;
        SizeType size_;
    };
}

namespace tsl::utility
{
    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    buffer<T, SizeType>::buffer(SizeType _capacity)
        : capacity_(_capacity)
        , size_(0)
    {
        data_ = new T[_capacity];
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    buffer<T, SizeType>::~buffer()
    {
        delete[] data_;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    void
    buffer<T, SizeType>::append(T const * _data, SizeType _size)
    {
        auto const new_size(size_ + _size);
        while (new_size > capacity_)
        {
            T * old_data(data_);
            capacity_ *= 2;
            data_ = new T[capacity_];
            std::copy(old_data, old_data + size_, data_);
            delete[] old_data;
        }
        std::copy(_data, _data + _size, data_ + size_);
        size_ = new_size;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    void
    buffer<T, SizeType>::clear()
    {
        size_ = 0;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    SizeType
    buffer<T, SizeType>::capacity()
    {
        return capacity_;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    T *
    buffer<T, SizeType>::data()
    {
        return data_;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    SizeType
    buffer<T, SizeType>::size()
    {
        return size_;
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    typename std::enable_if<std::is_same<T, char>::value, std::string>::type
    buffer<T, SizeType>::as_string()
    {
        return std::string(data_, size_);
    }

    //----------------------------------------------------------------------------------------------
    // Notes:
    //----------------------------------------------------------------------------------------------
    template <class T, class SizeType>
    typename std::enable_if<std::is_same<T, char>::value, std::string_view>::type
    buffer<T, SizeType>::as_view()
    {
        return std::string_view(data_, size_);
    }
}
#endif
