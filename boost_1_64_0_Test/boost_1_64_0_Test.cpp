// boost_1_64_0_Test.cpp : �������̨Ӧ�ó������ڵ㡣
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
//��������
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
	///////////////////////�ļ�ϵͳ����ϰ////////////////////////////////////////////////
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

    //////////////////////����ָ����ϰ////////////////////////////////////////////////
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
    shared_array<char> pshared(pchar);//pshared ����̬���� û������* ��->������

    //shared_ptr<std::vector>  std::vector<shared_ptr> ����������.

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
    ////////////////////////CRC ����ϰ////////////////////////////////////////////////
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

    /////////////////////BOOST_FOREACH ѭ�������㷨///////////////////////////////////////////////////
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

    /////////////////math.constants �����˺ܶ��ѧ���㳣��//////////////////////////////

    /////////////////rational �⴦�����////////////////////////////////////////////////

    ////////////////random �����///////////////////////////////////////////////////////

    ////////////////ignore_unused ���Զ����˵�δʹ�ó��ֵľ���//////////////////////////
    int unused;
    ignore_unused(unused);
    ///////////////////////////lexical_cast///////////////////////////////////////////////
    try
    {
        int lexical_int  = lexical_cast<int>("100"); //��ת����Ҫ�����쳣
    }
    catch(bad_lexical_cast &e)
    {
        std::cout << "error: " << e.what()<<std::endl;
    }

    int x;
    conversion::try_lexical_convert("0x100", x);//����Ҫ�����쳣.

    /////////////////////////Boost::format ��ʽ��/////////////////////////////////////////////////
    const format fmt("%|05d|\n%|-8.3f|\n%| 10s|\n%|05X|\n");
    std::cout << format(fmt) % 62 % 2.236 % "123456789" %48;

    //////////////////////string_ref////////////////////////////////////////////////////

    /////////////////////string_algo/////////////////////////////////////////////////////
    //1.to_upper  to_lower �˺�������_copy�汾.
    std::string str("Hello World!\n");
    
    //2.�ж�ʽ �㷨��������������
    //3.����
    //4.�޼� trim_left trim_right trim _if���_copy��
    //5.���� find_first find_last find_nth find_head find_tail find_token find_regex find
    //6.�滻��ɾ��
    //7.�ָ� find_all split
    //8.�ϲ� join
    //9.���ҡ��ָ������

    /////////////////////////tokenizer �ִ�/////////////////////////////////////////////////
    //1.ȱ��
    /////////////////////////xpressive ��ʹ�ô˿�ʱӦ����ʹ��try-catch/////////////////////////////////////////////////
    //1.basic_regex sregex��cregex
    //2.match_results smatch��cmatch
    //3.sub_match
    // regex_match ����ƥ��
    xpressive::cregex reg = xpressive::cregex::compile("a.c");
    assert(regex_match("abc", reg));

    //C++ 11 ���֤��֤�����ʾʽ�ַ�����ʾ R"---(\d{6}(1|2)\d{3}(0|1)\d[0-3]\d\d{3}{X|\d})---" VS2010��ʱ��֧��
    xpressive::cregex regID = xpressive::cregex::compile("(\\d{6}(1|2)\\d{3}(0|1)\\d[0-3]\\d\\d{3}{X|\\d})", xpressive::icase);
    // regex_search �������
    // regex_replace �����滻
    std::string str9a("9aB8");
    xpressive::sregex regStr = xpressive::sregex::compile("[a-zA-Z]", xpressive::icase);
    std::cout << "regex_replace = "<< xpressive::regex_replace(str9a, regStr,"0") << std::endl;
    // regex_iterator ������� sregex_iterator cregex_iterator
    // regex_token_iterator     sregex_token_iterator cregex_token_iterator

    //////////////////////////////////////////////////////////////////////////
    //1.BOOST_ASSERT BOOST_ASSERT_MSG
    BOOST_ASSERT(16 == 0x10);
    func(1);
    //2.test Unit Test Framework UTF

    ////////////////////���������ݽṹ//////////////////////////////////////////////////
    //vector deque list set map  forward_list unordered array dynamic_bitset bimap circular_buffer tuple variant multi_array property_tree

    //1.array ֻ��������֪�����С�� �����ٶȺܸߣ���Ҫ�ɱ���������std::vector
    array<int, 10> ar;
    ar[0] = 1;
    ar.back() = 10;
    BOOST_ASSERT(ar[ar.max_size() - 1] == 10);
    ar.assign(888);
    std::cout << std::dec; // std::oct �˽��ƣ�std::dec ʮ���ƣ� std::hex ʮ������;
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

    //2. dynamic_bitset �ṩ�ḻ��λ���㣬ͬʱ��̬�ɱ� ,����"����"
    //��ѧ������Ҫ�������0 1 e i ��

    ///////////////unordered ɢ������///////////////////////////////////////////////////////////
    //1. ���򼯺�set unordered_set unordered_multiset(���������ظ���Ԫ��)
    //2.����ӳ��map unordered_map unordered_multimap

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
    //1.���׳��쳣

    
    /////////////////////timer date_time chrono ��/////////////////////////////////////////////////////
    //1.timer ---> timer[ms��] progress_timer progress_disply

    std::vector<std::string> vec(100);
    std::ofstream fs("./test.txt");
    progress_display pd(v.size());

    BOOST_FOREACH(auto x, vec)
    {
        fs << x << std::endl;
        ++pd;
    }

    ///////////////////////date_time///////////////////////////////////////////////////
    //1.date �� ���׳��쳣 -->date_duration ���ڳ���.
    //2.time_duration Ĭ�Ͼ�ȷ��΢�� �����þ�ȷ������

    //////////////////BOOST �����̽��////////////////////////////////////////////////////////
    //1.Ԫ����
    typedef int meta_int;
    //using meta_int_using = int; Ҳ��˱�������֧�ִ��÷�
    //2.Ԫ����

    //////////////////boost::exception////////////////////////////////////////////////////////
    //1.exception
    //2.error_info 

    /////////////////boost::signals2/////////////////////////////////////////////////////////
    signals2::signal<void()> sig; //����һ���źŶ���
    sig.connect(&slots1); //���Ӳۺ���
    sig.connect(&slots2);
    sig();                //�����źţ������ۺ�������

    /////////////////boost.iostreams/////////////////////////////////////////////////////////
    //1.device source������� sink�����յ�
    //2.filter
    //3.stream stream_buffer
    //4.�������� io::copy

    /////////////////booset.serialization ���л�////////////////////////////////////////////
    archive::text_oarchive oa(std::cout);
    int i_archive = 1;
    oa << i_archive ;

    /////////////////atomic /////////////////////////////////////////////////////////
    //1.���岢��ʼ����2. store 3. load
    atomic<int> testAtomic(666);
    std::cout << "testAtomic.load = " << testAtomic.load() << std::endl;
    testAtomic.store(888);
    std::cout << "testAtomic.store = " << testAtomic.load() << std::endl;

    ////////////////thread//////////////////////////////////////////////////////////

    ////////////////bind//////////////////////////////////////////////////////////
    //1.����ͨ����
    std::cout << "boost::bind = " << bind(fBind, 1, 2)() << std::endl; //fBind(1,2);
    //2.�󶨳�Ա����
    demoBind aBind;
    std::cout << "boost::bind Class Fun = " << bind(&demoBind::fDemoBind, aBind, _1, 20)(10) << std::endl; //_1 ռλ��
    //3.��public��Ա����
    //4.�󶨺�������

    ////////////////boost::function//////////////////////////////////////////////////////////
    function<int(int, int)> func;
    func = fBind; //func �洢 ����fBind;
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
    //3.���ڻص�
    demoFunction df(10);
    df.accept(call_back_func);
    df.run();
    getchar();
    return 0; 
}

class do_not_copy : noncopyable //ֱ�Ӽ̳пɽ��ÿ��� ���� ����.
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
    BOOST_ASSERT_MSG(x != 0, "divided by zero"); //����Ϊfalse ��ʾ����ʧ��.
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
