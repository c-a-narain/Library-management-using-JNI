#include <jni.h> // JNI header provided by JDK
#include <iostream>    // C++ standard IO header
#include "HelloJNI.h"  // Generated
#include <pqxx/pqxx>
#include <string>

using namespace pqxx;
using namespace std;

// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv* env, jobject thisObj)
{
    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }
        pqxx::work W(C);

        pqxx::result response = W.exec("SELECT * FROM books ORDER BY BOOK_ID");

        for (size_t i = 0; i < response.size(); i++)
        {
            std::cout << response[i][0] << " " << response[i][1] << " " << response[i][2] << " " << response[i][3] << " " << response[i][4] << " " << response[i][5] << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return;
}

JNIEXPORT void JNICALL Java_HelloJNI_update(JNIEnv*, jobject, jint bid, jint q) {


    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }

        pqxx::work W(C);

        W.exec("UPDATE BOOKS set QUANTITY = " + std::to_string(q) + " where BOOK_ID=" + std::to_string(bid) + "");
        W.commit();
        cout << "Records updated successfully" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

}

JNIEXPORT void JNICALL Java_HelloJNI_add (JNIEnv *env, jobject thisObj, jint bid, jstring name, jstring author, jstring edd, jstring pub, jint q) {
    try {
        const char* name1 = env->GetStringUTFChars(name, NULL);
        const char* author1 = env->GetStringUTFChars(author, NULL);
        const char* edd1 = env->GetStringUTFChars(edd, NULL);
        const char* pub1 = env->GetStringUTFChars(pub, NULL);


        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }

        pqxx::work W(C);
        W.exec("INSERT INTO BOOKS VALUES (" + std::to_string(bid) + ",'" + name1 + "','" + author1 + "','" + edd1 + "','" + pub1 + "'," + std::to_string(q) + "); ");

        W.commit();

        cout << "Records created successfully" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}

JNIEXPORT void JNICALL Java_HelloJNI_delete(JNIEnv* env, jobject thisObj, jint bid) {
    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }

        pqxx::work W(C);
        W.exec("DELETE FROM BOOKS WHERE BOOK_ID=" + std::to_string(bid) + " ");
        W.commit();
        cout << "Records Deleted successfully" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}

JNIEXPORT void JNICALL Java_HelloJNI_user_1list(JNIEnv* env, jobject thisObj) {
    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);
        pqxx::result response = worker.exec("SELECT * FROM user_login");
        for (size_t i = 0; i < response.size(); i++)
        {
            std::cout << response[i][1] << std::endl;
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}

JNIEXPORT jboolean JNICALL Java_HelloJNI_checkuser(JNIEnv* env, jobject thisObj, jstring usname, jstring pswd) {
    try
    {        
        const char* usname1 = env->GetStringUTFChars(usname, NULL);
        const char* pswd1 = env->GetStringUTFChars(pswd, NULL);

        std::string us = usname1;
        std::string ps = pswd1;
 
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM user_login");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (us.compare(response[i][1].as<string>()) == 0 && ps.compare(response[i][2].as<string>()) == 0)
            {
                return 1;
            }
        }
        return 0;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    system("pause");

}

JNIEXPORT jboolean JNICALL Java_HelloJNI_checkadmin(JNIEnv* env, jobject thisObj, jstring usname, jstring pswd) {
    try
    {
        const char* usname1 = env->GetStringUTFChars(usname, NULL);
        const char* pswd1 = env->GetStringUTFChars(pswd, NULL);

        std::string us = usname1;
        std::string ps = pswd1;

        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM admin_login");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (us.compare(response[i][1].as<string>()) == 0 && ps.compare(response[i][2].as<string>()) == 0)
            {
                return 1;
            }
        }
        return 0;

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    system("pause");

}

JNIEXPORT void JNICALL Java_HelloJNI_borrow (JNIEnv* env, jobject thisObj, jint bid, jstring username)
{
    int uid, quant;
    
    try
    {
        const char* name1 = env->GetStringUTFChars(username, NULL);

        string usname = name1;

        pqxx::connection connectionObject("host = localhost port = 5432 dbname = postgres user = postgres password = caNarain@2002");

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM user_login");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (usname.compare(response[i][1].as<string>()) == 0)
            {
                uid = response[i][0].as<int>();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    try {
        pqxx::connection connectionObject("host = localhost port = 5432 dbname = postgres user = postgres password = caNarain@2002");

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM books");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (to_string(bid).compare(response[i][0].as<string>()) == 0)
            {
                quant = response[i][5].as<int>();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    system("pause");
    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }

        pqxx::work W(C);

        W.exec("INSERT INTO USER_DATA(book_id,user_id) VALUES(" + std::to_string(bid) + "," + std::to_string(uid) + ")");

        W.exec("UPDATE BOOKS set QUANTITY=QUANTITY-1 where BOOK_ID=" + std::to_string(bid) + " AND QUANTITY>-1;");
        W.commit();
        cout << "Books Borrowed successfully" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

}

JNIEXPORT void JNICALL Java_HelloJNI_Return(JNIEnv* env, jobject thisObj, jint bid, jstring username) {
    int uid;

    try
    {
        const char* name1 = env->GetStringUTFChars(username, NULL);

        string usname = name1;

        pqxx::connection connectionObject("host = localhost port = 5432 dbname = postgres user = postgres password = caNarain@2002");

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM user_login");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (usname.compare(response[i][1].as<string>()) == 0)
            {
                uid = response[i][0].as<int>();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection C(connectionString.c_str());

        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }

        pqxx::work W(C);

        /* Execute SQL query */
        W.exec("DELETE FROM USER_DATA WHERE BOOK_ID=" + std::to_string(bid) + " AND USER_ID=" + std::to_string(uid) + " ");
        W.exec("UPDATE BOOKS set QUANTITY = QUANTITY+1 WHERE BOOK_ID=" + std::to_string(bid) + " ");
        W.commit();
        cout << "Records Deleted successfully" << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }


}

JNIEXPORT void JNICALL Java_HelloJNI_myBooks (JNIEnv* env, jobject thisObj, jstring username)
{
    int uid;

    try
    {
        const char* name1 = env->GetStringUTFChars(username, NULL);

        string usname = name1;

        pqxx::connection connectionObject("host = localhost port = 5432 dbname = postgres user = postgres password = caNarain@2002");

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("SELECT * FROM user_login");

        for (size_t i = 0; i < response.size(); i++)
        {
            if (usname.compare(response[i][1].as<string>()) == 0)
            {
                uid = response[i][0].as<int>();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password =caNarain@2002";

        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);

        pqxx::result response = worker.exec("Select a.book_id,a.book_name,a.author_name,a.edition,a.publisher,b.return_date,b.borrow_date FROM BOOKS a join user_data b on a.book_id=b.book_id WHERE b.user_id= " + std::to_string(uid) + ";");

        for (size_t i = 0; i < response.size(); i++)
        {
            std::cout << response[i][0] << " " << response[i][1] << " " << response[i][2] << " " << response[i][3] << " " << response[i][4] << " " << response[i][5]<< " " << response[i][6] << std::endl;
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}


int main() {
    JNIEXPORT void Java_HelloJNI_sayHello();
}
