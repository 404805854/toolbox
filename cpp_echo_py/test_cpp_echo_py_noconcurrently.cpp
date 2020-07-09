#include <python3.6m/Python.h> //需要安装python
#include <iostream>
#include <string>
using namespace std;

int main () {

    //使用python之前，要调用Py_Initialize();这个函数进行初始化
    Py_Initialize();

    if(!Py_IsInitialized()) return 0;

    //导入环境变量
    PyRun_SimpleString("import sys");

    //python脚本路径
    PyRun_SimpleString("sys.path.append('./')"); //该语句的含义是python文件放在生成的可执行文件同一路径下

    /*
    使用PyRun_SimpleString("")函数导入python代码中所有的包及对象
    该函数类似于宏命令
    python文件内的这些语句可以不删除，因为不会被执行到
    eg:
    PyRun_SimpleString("import numpy as np");
    ·
    ·
    ·
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import base64");

    PyRun_SimpleString("RATE = 16000");
    ·
    ·
    ·
    PyRun_SimpleString("WIN_LEN = 0.02");
    PyRun_SimpleString("WIN_STEP = 0.01");
    */

    // PyImport_ImportModule函数载入python脚本，参数为为python脚本名称（不含后缀），因为是模块化的导入，所以当代码处于运行期的时候就会生成一个.pyc文件
    PyObject *pModule = NULL;
    pModule = PyImport_ImportModule("pytest");

    if (!pModule)
    {
        cout << "Python get module failed." << endl;
        return 0;
    }

    cout << "Python get module succeed." << endl;

    //获取Insert模块内DLC函数  
    PyObject* pv = PyObject_GetAttrString(pModule, "DLC");
    if (!pv || !PyCallable_Check(pv))
    {
        cout << "Can't find funftion (DLC)" << endl;
        return 0;
    }
    cout << "Get function (DLC) succeed." << endl;

    //初始化要传入的参数  
    PyObject* args = PyTuple_New(1);//设置传入参数的个数
    PyObject* arg1 = Py_BuildValue("s","./");

    //将arg1配置为arg带入的第一个参数  
    PyTuple_SetItem(args, 0, arg1);
    
    cout << "Set item succeed." << endl;

    //传入参数调用函数，并获取返回值  
    PyObject* pRet = PyObject_CallObject(pv, args);

    if (pRet != NULL) {
        char* retstr = NULL;
        PyArg_Parse(pRet, "s", &retstr);
        cout << retstr << endl;
    }
    else return 0;

    cout << "Succeed." << endl;

    //调用Py_Finalize，这个与Py_Initialize相对应的
    Py_Finalize();
    return 0;
}
