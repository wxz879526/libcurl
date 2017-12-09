// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "curl/curl.h"

size_t string_write(char *ptr, size_t size, size_t nmemb, std::string &str)
{
	size_t total = size * nmemb;
	if (total)
	{
		str.append(ptr, total);
	}

	return total;
}

int main()
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl)
	{
		struct curl_slist *headers = nullptr;
		headers = curl_slist_append(headers, "Authorization:Basic bWF4aHViOm1heGh1YkAxMjM=");
		headers = curl_slist_append(headers, "Content-Type: application/json");

		std::string content;
		std::string json = "{\"isPublic\":true, \"name\":\"shsishsih\", \"accessKey\":\"\", \"deviceName\":\"ssssss\", \"author\":\"kkkkkk\", \"expirationTime\":9999999999, \"permissions\":\"get,post\", \"isNeedNotifying\":1}";
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
		curl_easy_setopt(curl, CURLOPT_URL, "https://res.maxhub.vip/api/client/shares");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, string_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform falied: %s\n", curl_easy_strerror(res));
		}

		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

    return 0;
}

