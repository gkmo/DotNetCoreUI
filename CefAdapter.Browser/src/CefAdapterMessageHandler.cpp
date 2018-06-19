
#include <iostream>
#include "CefAdapterMessageHandler.h"

namespace 
{
    std::map<int64, CefRefPtr<CefMessageRouterBrowserSide::Callback>> _queries;
}

CefAdapterMessageHandler::CefAdapterMessageHandler(QueryCallback queryCallback)
{
    _queryCallback = queryCallback;    
}

CefAdapterMessageHandler::~CefAdapterMessageHandler()
{
    _queryCallback = NULL;
}

void OnSuccess(long queryId, const char* message)
{
    std::cout << "CefAdapterMessageHandler::OnSuccess = " << message << "; Query Id = " << queryId << std::endl;    

    auto callback = _queries[queryId];

    _queries.erase(queryId);

    callback->Success(message);
}

void OnFailure(long queryId, int errorCode, const char* message)
{
    std::cout << "CefAdapterMessageHandler::OnFailure = " << errorCode << " - " << message << "; Query Id = " << queryId << std::endl;    

    auto callback = _queries[queryId];

    _queries.erase(queryId);

    callback->Failure(errorCode, message);
}

bool CefAdapterMessageHandler::OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 queryId,
                         const CefString& request, bool persistent, CefRefPtr<Callback> callback)
{
    std::cout << "CefAdapterMessageHandler::OnQuery = " << request.ToString() << "; Query Id = " << queryId << std::endl;    
    
    _queries[queryId] = callback;

    if(_queryCallback(browser->GetIdentifier(), frame->GetIdentifier(), queryId, request.ToString().c_str(), &OnSuccess, &OnFailure))
    {
        return true;
    }

    _queries.erase(queryId);    

    return false;
}