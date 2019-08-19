#pragma once
#ifndef included_tsl_utility_get_data_from_url_08September2018_
#define included_tsl_utility_get_data_from_url_08September2018_

#ifndef _MSC_VER
#   ident "$Id: $"
#endif

/*
    Created: 08 September 2018

    Author: Tony Thompson <ajthomps51@gmail.com>
*/

//! @file
//! Provides tsl::utility::get_data_from_url()

#include <string_view>
#include <curl/curl.h>
#include "buffer.h"

namespace tsl::utility
{
    buffer<char>
    get_data_from_url(std::string_view const & _url);
}

namespace tsl::utility::details
{
    size_t
    writeFunction(void * ptr, size_t size, size_t nmemb, buffer<char> * data);
}

namespace tsl::utility
{
    inline buffer<char>
    get_data_from_url(std::string_view const & _url)
    {
        buffer<char> result(1024);
        buffer<char> header(1024);
        auto curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, _url.data());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, details::writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
        char * url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
        return result;
    }
}

namespace tsl::utility::details
{
    //**********************************************************************************************
    // Notes:
    //----------------------------------------------------------------------------------------------
    inline size_t
    writeFunction(void * ptr, size_t size, size_t nmemb, buffer<char> * data)
    {
        data->append((char *)ptr, size * nmemb);
        return size * nmemb;
    }
}
#endif
