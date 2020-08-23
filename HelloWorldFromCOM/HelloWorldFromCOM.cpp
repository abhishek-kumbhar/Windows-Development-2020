//#include <stdafx.h>
#include <sapi.h>


/*
int main(int argc, char* argv[])
{
    ISpVoice* pVoice = NULL;

    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (SUCCEEDED(hr))
    {
        hr = pVoice->Speak(L"Hello Abhishek", 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    ::CoUninitialize();
    return TRUE;
}

*/




//#include <stdafx.h>
#include <sapi.h>

int main(int argc, char* argv[])
{
    TCHAR str[];
    ISpVoice* pVoice = NULL;

    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (SUCCEEDED(hr))
    {
        hr = pVoice->Speak(L"Hello world", 0, NULL);

        // Change pitch
        hr = pVoice->Speak(L"India is my country. all indians are my brothers are sisters. i love my country.", SPF_IS_XML, NULL);
        pVoice->Release();
        pVoice = NULL;
    }
    ::CoUninitialize();
    return TRUE;
}