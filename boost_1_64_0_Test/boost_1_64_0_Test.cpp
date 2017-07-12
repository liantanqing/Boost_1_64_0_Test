// boost_1_64_0_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "boost/timer.hpp"
#include "boost/progress.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/filesystem.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/crc.hpp"
#include "boost/foreach.hpp"
#include "boost/assign.hpp"
#include "boost/math/constants/constants.hpp"
#include "boost/noncopyable.hpp"
#include "boost/core/ignore_unused.hpp"
#include "boost/optional.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/format.hpp"
#include "boost/utility/string_ref.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/xpressive/xpressive_dynamic.hpp"
#include "boost/assert.hpp"
#include "boost/test/unit_test.hpp"
#include "boost/array.hpp"
#include "boost/dynamic_bitset.hpp"
#include "boost/unordered_set.hpp"
#include "boost/unordered_map.hpp"
#include "boost/any.hpp"
#include "boost/variant.hpp"
#include "boost/circular_buffer.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "boost/exception/all.hpp"
#include "boost/signals2.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/atomic.hpp"
#include "boost/bind.hpp"
#include "boost/function.hpp"
#include <vector>
using namespace boost;

double func(int x);
void slots1();
void slots2();
//工厂函数
template <typename T>
any make_ptr_any(T* p = 0)
{
    return any(shared_ptr<T>(p));
}

int fBind(int a, int b)
{
    return a + b;
}

struct demoBind
{
    int fDemoBind(int a, int b)
    {
        return a + b;
    }
};

class demoFunction{
public:
    demoFunction(int i): n(i){}
    demoFunction(std::string getStr): str(getStr){}
    template<typename CallBack>
    void accept(CallBack f)
    {
        func = f;
    }
    void run()
    {
        str = "using std::function for callback";
        func(n);
    }

private:
    typedef function<void(int)> func_t;
    typedef function<std::string()> func_str;
    func_t func;
    func_str func2;
    int n;
    std::string str;
};

void call_back_func(int i)
{
    std::cout << "call_back_func(int i) = " << i * 2 << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	///////////////////////文件系统库练习////////////////////////////////////////////////
    namespace bf = boost::filesystem;
    bf::path dirPath("F:\\xunlei");
    bool result = bf::is_directory(dirPath);
    printf("Path is a directory : %d\n", result);
    std::string removeFolder = "E:\\temp";
    if (bf::is_directory(removeFolder))
    {
        try {
        bf::remove_all(removeFolder);
        }
        catch(boost::filesystem::filesystem_error e) { 
            // do the needful 
            printf("err code = %s",e);
        } 
    }

    //////////////////////智能指针练习////////////////////////////////////////////////
    scoped_ptr<int> scopedp_int(new int);
    if (scopedp_int)
    {
        *scopedp_int = 100;
        printf("p_int = %d\n", *scopedp_int);
    }

    //unique_ptr<int> uniquep_int(new int);
    //unique_ptr<int[]> uniqueparray_int(new int[10]);
    //auto p = boost::make_unique<int>(10);
    
    scoped_array<int> p_intarray(new int[100]);
    
    shared_ptr<int> sp(new int(10));
    auto spmake = make_shared<int>(10);

    char* pchar = new char[100];
    shared_array<char> pshared(pchar);//pshared 代理动态数组 没有重载* 、->操作符

    //shared_ptr<std::vector>  std::vector<shared_ptr> 来操作数组.

    typedef std::vector<shared_ptr<int>> ver_sharedptr;
    ver_sharedptr verShared(10);
    int i_ver = 0;
    std::cout << "vector<shared_ptr<int>> = " ;
    for (auto pos = verShared.begin(); pos != verShared.end(); ++pos)
    {
        (*pos) = make_shared<int>(++i_ver);
        std::cout <<  *(*pos) << ", ";
    }
    std::cout << std::endl;
    ////////////////////////CRC 库练习////////////////////////////////////////////////
    crc_32_type crc32;
    std::cout << std::hex;
    std::cout << crc32.checksum() << std::endl;

    char szCh[] = "12345";
    crc32.reset();
    crc32.process_block(szCh, szCh + 5);
    std::cout << crc32.checksum() << std::endl;
    crc32.reset();
    crc32.process_block(szCh, szCh + 5);
    std::cout << crc32.checksum() << std::endl;
    //////////////////////////////////////////////////////////////////////////

    /////////////////////BOOST_FOREACH 循环遍历算法///////////////////////////////////////////////////
    using namespace boost::assign;
    std::vector<int> v = (list_of(1), 2, 3, 4, 5);
    BOOST_FOREACH(auto x, v)
    {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    /////////////////////assign/////////////////////////////////////////////////////
    std::vector<int> assign_v = list_of(-1)(-2)(-3)(-4);
    assign_v += 1, 2, 3, 4, 5, 6*6; //override operator +=

    push_back(assign_v)(7)(8)(9);

    /////////////////math.constants 定义了很多科学计算常数//////////////////////////////

    /////////////////rational 库处理分数////////////////////////////////////////////////

    ////////////////random 随机数///////////////////////////////////////////////////////

    ////////////////ignore_unused 忽略定义了但未使用出现的警告//////////////////////////
    int unused;
    ignore_unused(unused);
    ///////////////////////////lexical_cast///////////////////////////////////////////////
    try
    {
        int lexical_int  = lexical_cast<int>("100"); //此转换需要捕获异常
    }
    catch(bad_lexical_cast &e)
    {
        std::cout << "error: " << e.what()<<std::endl;
    }

    int x;
    conversion::try_lexical_convert("0x100", x);//不需要捕获异常.

    /////////////////////////Boost::format 格式化/////////////////////////////////////////////////
    const format fmt("%|05d|\n%|-8.3f|\n%| 10s|\n%|05X|\n");
    std::cout << format(fmt) % 62 % 2.236 % "123456789" %48;

    //////////////////////string_ref////////////////////////////////////////////////////

    /////////////////////string_algo/////////////////////////////////////////////////////
    //1.to_upper  to_lower 此函数带有_copy版本.
    std::string str("Hello World!\n");
    
    //2.判断式 算法方法、函数对象
    //3.分类
    //4.修剪 trim_left trim_right trim _if版和_copy版
    //5.查找 find_first find_last find_nth find_head find_tail find_token find_regex find
    //6.替换和删除
    //7.分割 find_all split
    //8.合并 join
    //9.查找、分割迭代器

    /////////////////////////tokenizer 分词/////////////////////////////////////////////////
    //1.缺陷
    /////////////////////////xpressive 在使用此库时应当总使用try-catch/////////////////////////////////////////////////
    //1.basic_regex sregex、cregex
    //2.match_results smatch、cmatch
    //3.sub_match
    // regex_match 正则匹配
    xpressive::cregex reg = xpressive::cregex::compile("a.c");
    assert(regex_match("abc", reg));

    //C++ 11 身份证验证正则表示式字符串表示 R"---(\d{6}(1|2)\d{3}(0|1)\d[0-3]\d\d{3}{X|\d})---" VS2010暂时不支持
    xpressive::cregex regID = xpressive::cregex::compile("(\\d{6}(1|2)\\d{3}(0|1)\\d[0-3]\\d\\d{3}{X|\\d})", xpressive::icase);
    // regex_search 正则查找
    // regex_replace 正则替换
    std::string str9a("9aB8");
    xpressive::sregex regStr = xpressive::sregex::compile("[a-zA-Z]", xpressive::icase);
    std::cout << "regex_replace = "<< xpressive::regex_replace(str9a, regStr,"0") << std::endl;
    // regex_iterator 正则迭代 sregex_iterator cregex_iterator
    // regex_token_iterator     sregex_token_iterator cregex_token_iterator

    //////////////////////////////////////////////////////////////////////////
    //1.BOOST_ASSERT BOOST_ASSERT_MSG
    BOOST_ASSERT(16 == 0x10);
    func(1);
    //2.test Unit Test Framework UTF

    ////////////////////容器和数据结构//////////////////////////////////////////////////
    //vector deque list set map  forward_list unordered array dynamic_bitset bimap circular_buffer tuple variant multi_array property_tree

    //1.array 只能运用已知数组大小， 运行速度很高；需要可变数组请用std::vector
    array<int, 10> ar;
    ar[0] = 1;
    ar.back() = 10;
    BOOST_ASSERT(ar[ar.max_size() - 1] == 10);
    ar.assign(888);
    std::cout << std::dec; // std::oct 八进制；std::dec 十进制； std::hex 十六进制;
    BOOST_FOREACH(auto x, ar)
    {
        std::cout << x << ",";
    }

    int* p = ar.c_array();
    *(p + 5) = 666;
    std::cout << ar[5] << std::endl;

    ar.at(8) = 999;
    std::sort(ar.begin(), ar.end());
    BOOST_FOREACH(auto x, ar)
    {
        std::cout << x << ",";
    }

    //2. dynamic_bitset 提供丰富的位运算，同时动态可变 ,不是"容器"
    //数学中最重要的五个数0 1 e i π

    ///////////////unordered 散列容器///////////////////////////////////////////////////////////
    //1. 无序集合set unordered_set unordered_multiset(可以容纳重复的元素)
    //2.无序映射map unordered_map unordered_multimap

    ////////////////bimap//////////////////////////////////////////////////////////

    ///////////////circular_buffer/////////////////////////////////////////////////
    circular_buffer<int> cb(3);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    ////////////////tuple//////////////////////////////////////////////////////////
    typedef tuple<int, std::string, double> my_tuple;//max 10-tuple
    my_tuple t1 = make_tuple(1, "Hello Tuple", 100);//3-tuple
    std::cout << "\nmy_tuple = " << t1 << std::endl;

    ////////////////any//////////////////////////////////////////////////////////
    any a;
    a = std::string("\nHello Any\n");
    std::cout << any_cast<std::string>(a);
    
    ////////////////variant //////////////////////////////////////////////////////////
    typedef variant<int, double, std::string> var_t;
    var_t var("variant demo");
    //v = "variant demo";
    //std::cout << *get<std::string>(&v); 
    
    ////////////////property_tree//////////////////////////////////////////////////////////
    //1.会抛出异常

    
    /////////////////////timer date_time chrono 库/////////////////////////////////////////////////////
    //1.timer ---> timer[ms级] progress_timer progress_disply

    std::vector<std::string> vec(100);
    std::ofstream fs("./test.txt");
    progress_display pd(v.size());

    BOOST_FOREACH(auto x, vec)
    {
        fs << x << std::endl;
        ++pd;
    }

    ///////////////////////date_time///////////////////////////////////////////////////
    //1.date 类 会抛出异常 -->date_duration 日期长度.
    //2.time_duration 默认精确到微妙 可设置精确到纳秒

    //////////////////BOOST 程序库探秘////////////////////////////////////////////////////////
    //1.元数据
    typedef int meta_int;
    //using meta_int_using = int; 也许此编译器不支持此用法
    //2.元函数

    //////////////////boost::exception////////////////////////////////////////////////////////
    //1.exception
    //2.error_info 

    /////////////////boost::signals2/////////////////////////////////////////////////////////
    signals2::signal<void()> sig; //定义一个信号对象
    sig.connect(&slots1); //连接槽函数
    sig.connect(&slots2);
    sig();                //发送信号，触发槽函数调用

    /////////////////boost.iostreams/////////////////////////////////////////////////////////
    //1.device source流的起点 sink流的终点
    //2.filter
    //3.stream stream_buffer
    //4.流处理函数 io::copy

    /////////////////booset.serialization 序列化////////////////////////////////////////////
    archive::text_oarchive oa(std::cout);
    int i_archive = 1;
    oa << i_archive ;

    /////////////////atomic /////////////////////////////////////////////////////////
    //1.定义并初始化、2. store 3. load
    atomic<int> testAtomic(666);
    std::cout << "testAtomic.load = " << testAtomic.load() << std::endl;
    testAtomic.store(888);
    std::cout << "testAtomic.store = " << testAtomic.load() << std::endl;

    ////////////////thread//////////////////////////////////////////////////////////

    ////////////////bind//////////////////////////////////////////////////////////
    //1.绑定普通函数
    std::cout << "boost::bind = " << bind(fBind, 1, 2)() << std::endl; //fBind(1,2);
    //2.绑定成员函数
    demoBind aBind;
    std::cout << "boost::bind Class Fun = " << bind(&demoBind::fDemoBind, aBind, _1, 20)(10) << std::endl; //_1 占位符
    //3.绑定public成员变量
    //4.绑定函数对象

    ////////////////boost::function//////////////////////////////////////////////////////////
    function<int(int, int)> func;
    func = fBind; //func 存储 函数fBind;
    if (func)
    {
        std::cout << "boost::function<int(int, int)> = " << func(11, 22) << std::endl;
    }
    //
    function<int(int, int)> func2;
    func2 = bind(&demoBind::fDemoBind, &aBind, _1, _2);
    if (func2)
    {
        std::cout << "boost::function<int(int, int)> = " << func2(33, 44) << std::endl;
    }
    //3.用于回调
    demoFunction df(10);
    df.accept(call_back_func);
    df.run();
    getchar();
    return 0; 
}

class do_not_copy : noncopyable //直接继承可禁用拷贝 复制 构造.
{
public:
protected:
private:
};

optional<int> testOptional(int x)
{
    optional<int> a;
    optional<int> b(boost::none);
    return b;
}

double func(int x)
{
    BOOST_ASSERT_MSG(x != 0, "divided by zero"); //断言为false 表示断言失败.
    return 1.0 / x;
}

void slots1()
{
    std::cout << "\nslots1 called" << std::endl;
}

void slots2()
{
    std::cout << "slots2 called" << std::endl;
}
