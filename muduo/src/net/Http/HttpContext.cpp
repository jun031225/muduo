#include"HttpContext.h"
#include"Buffer.h"
#include"Logging.h"

// GET /index.html?id=acer HTTP/1.1
//解析请求行
bool HttpContext::processRequestLine(const char *begin, const char *end)
{
    bool succeed = false;
    const char *start = begin;
    const char *space = std::find(start, end, ' ');//分隔请求方法(GET)
    if(space != end && request_.setMethod(start, space))//判断请求方法是否有效
    {
        start = space + 1;//跳过空格
        space = std::find(start, end,' ');//寻找下一个空格
        if(space != end)
        {
            const char *question = std::find(start, space, '?');//分隔path和query
            if(question != space)
            {
                request_.setPath(start, question);//设定请求路径
                request_.setQuery(question, space);//设定询问参数
            }
            else//无询问参数
            {
                request_.setPath(start, space);
            }

            start = space + 1;
            succeed = (end - start == 8 && std::equal(start, end -1, "HTTP/1."));//是否匹配版本HTTP1.
            if(succeed)
            {
                if(*(end - 1) == '1')
                {
                    request_.setVersion(HttpRequest::kHttp11);
                }
                else if(*(end - 1) == '0')
                {
                    request_.setVersion(HttpRequest::kHttp10);
                }
                else
                {
                    succeed = false;
                }
            }
        }
    }
    return succeed;
}

//解析Http请求
bool HttpContext::parseRequest(Buffer *buf, TimeStamp receiveTime)
{
    bool ok = true;
    bool hasMore = true;// 初始化状态为 true，表示还有更多内容需要解析
    while(hasMore)
    {
        if(state_ == kExpectRequestLine)// 如果当前状态为解析请求行状态
        {
            const char *crlf = buf->findCRLF();// 查找缓冲区中的 CRLF（回车换行）序列
            if(crlf)
            {
                ok = processRequestLine(buf->peek(), crlf);//处理请求行
                if(ok)
                {
                    request_.setReceiveTime(receiveTime);//设定请求接受时间
                    buf->repositionUntil(crlf + 2);//移动到请求头部
                    state_ = kExpectHeaders;//设定解析状态为解析头部状态
                }
                else
                {
                    hasMore = false;
                }
            }
            else
            {
                hasMore = false;
            }
        }
         // Host: 127.0.0.1:8002
        else if(state_ == kExpectHeaders)// 如果当前状态为解析请求头部状态
        {
            const char *crlf = buf->findCRLF();//查找crlf
            if(crlf)
            {
                const char *colon = std::find(buf->peek(), crlf, ':');
                if(colon != crlf)
                {
                    request_.addHeader(buf->peek(), colon, crlf);//添加请求头部
                }
                else
                {
                    state_ = kGotAll;//解析结束
                    hasMore = false;
                }
                buf->repositionUntil(crlf + 2);//复位缓冲区指针
            }
            else
            {
                hasMore = false;
            }
        }
        else if(state_ == kExpectBody)
        {

        }
    }
    return ok;
}