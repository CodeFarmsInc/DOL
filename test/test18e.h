#define ZZascii

struct Faculty {
public:
    ZZ_EXT_Faculty
public:
    int ssn;
    int salary;
    int phone;
    Faculty(){ZZ_INIT(Faculty);};
    ~Faculty(){ZZ_CHECK(Faculty);};
};
ZZ_FORMAT(Faculty,"%d %d %d,ssn,salary,phone");
struct Student {
public:
    ZZ_EXT_Student
public:
    int id;
    int phone;
    int bDay;
    Student(){ZZ_INIT(Student);};
    ~Student(){ZZ_CHECK(Student);};
};
ZZ_FORMAT(Student,"%d %d %d,id,phone,bDay");
struct Course {
public:
    ZZ_EXT_Course
public:
    float credit;
    Course(){ZZ_INIT(Course);};
    ~Course(){ZZ_CHECK(Course);};
};
ZZ_FORMAT(Course,"%f,credit");
struct Department {
public:
    ZZ_EXT_Department
public:
    int phone;
    int officeNum;
    Department(){ZZ_INIT(Department);};
    ~Department(){ZZ_CHECK(Department);};
};
ZZ_FORMAT(Department,"%d %d,phone,officeNum");
struct Advisor {
public:
    ZZ_EXT_Advisor
public:
    Advisor(){ZZ_INIT(Advisor);};
    ~Advisor(){ZZ_CHECK(Advisor);};
};
ZZ_FORMAT(Advisor,"");
struct HasTaken {
public:
    ZZ_EXT_HasTaken
public:
    int semester;
    int grade;
    HasTaken(){ZZ_INIT(HasTaken);};
    ~HasTaken(){ZZ_CHECK(HasTaken);};
};
ZZ_FORMAT(HasTaken,"%d %d,semester,grade");
struct IsTaking {
public:
    ZZ_EXT_IsTaking
public:
    int semester;
    IsTaking(){ZZ_INIT(IsTaking);};
    ~IsTaking(){ZZ_CHECK(IsTaking);};
};
ZZ_FORMAT(IsTaking,"%d,semester");
struct IsTeaching {
public:
    ZZ_EXT_IsTeaching
public:
    IsTeaching(){ZZ_INIT(IsTeaching);};
    ~IsTeaching(){ZZ_CHECK(IsTeaching);};
};
ZZ_FORMAT(IsTeaching,"");
struct WorksFor {
public:
    ZZ_EXT_WorksFor
public:
    WorksFor(){ZZ_INIT(WorksFor);};
    ~WorksFor(){ZZ_CHECK(WorksFor);};
};
ZZ_FORMAT(WorksFor,"");
struct HasMajor {
public:
    ZZ_EXT_HasMajor
public:
    HasMajor(){ZZ_INIT(HasMajor);};
    ~HasMajor(){ZZ_CHECK(HasMajor);};
};
ZZ_FORMAT(HasMajor,"");
struct Offers {
public:
    ZZ_EXT_Offers
public:
    Offers(){ZZ_INIT(Offers);};
    ~Offers(){ZZ_CHECK(Offers);};
};
ZZ_FORMAT(Offers,"");
struct Header { /* general header, for the hash table */
public:
    ZZ_EXT_Header
public:
    Header(){ZZ_INIT(Header);};
    ~Header(){ZZ_CHECK(Header);};
};
ZZ_FORMAT(Header,"");
struct GenName { /* general name entry, for hash table */
public:
    ZZ_EXT_GenName
public:
    void ini(void){ZZ_INIT(GenName);};
    GenName(){ZZ_INIT(GenName);};
    ~GenName(){ZZ_CHECK(GenName);};
};
ZZ_FORMAT(GenName,"");

ZZ_HYPER_SELF_ID(Faculty);
ZZ_HYPER_SELF_ID(Student);
ZZ_HYPER_SELF_ID(Course);
ZZ_HYPER_SELF_ID(Department);
ZZ_HYPER_HASH(names,Header,GenName);
ZZ_HYPER_SINGLE_TRIANGLE(faculties,Header,Faculty);
ZZ_HYPER_SINGLE_TRIANGLE(students,Header,Student);
ZZ_HYPER_SINGLE_TRIANGLE(courses,Header,Course);
ZZ_HYPER_SINGLE_TRIANGLE(departments,Header,Department);
ZZ_HYPER_NAME(fName,Faculty);
ZZ_HYPER_NAME(fOffice,Faculty);
ZZ_HYPER_NAME(sName,Student);
ZZ_HYPER_NAME(sAddress,Student);
ZZ_HYPER_NAME(courseNum,Course);
ZZ_HYPER_NAME(dName,Department);
ZZ_HYPER_NAME(hName,GenName);
ZZ_HYPER_GENERAL_LINK(hObject,GenName);

ZZ_HYPER_1_TO_1(advisor,Faculty,Advisor,Student);
ZZ_HYPER_M_TO_N(hasTaken,Student,HasTaken,Course);
ZZ_HYPER_M_TO_N(isTaking,Student,IsTaking,Course);
ZZ_HYPER_1_TO_N(isTeaching,Faculty,IsTeaching,Course);
ZZ_HYPER_M_TO_1(worksFor,Faculty,WorksFor,Department);
ZZ_HYPER_M_TO_1(hasMajor,Student,HasMajor,Department);
ZZ_HYPER_1_TO_N(offers,Department,Offers,Course);

ZZ_HYPER_UTILITIES(util);
