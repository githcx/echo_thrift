namespace cpp echo

struct TestReq
{
  1: required i32 num;
  2: required string str;
  3: required map<string, i64> person_age;
  4: required list<double> rand_data;
}

service EchoService {
    string Echo(1:string msg, 2: TestReq test)
}


