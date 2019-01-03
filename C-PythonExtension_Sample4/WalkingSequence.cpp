// Reference: https://www.52pojie.cn/thread-842349-1-1.html

#include<Python.h>
#include<iostream>

using namespace std;

/*	The General
*		the function of this extension sample
*			is generally like this: (python scripts following)
*
*			>>>mylist = [1, 2, 3, 4, 5]
*			>>>for index in range(len(mylist)):
*					v = mylist[index]
*					print(v)
*
*		we re now going to realise this function by C
*/

/*
* 遍历列表
*/
static PyObject* WalkingSequence_WalkingDownList(
	PyObject* self,
	PyObject* args
) {
	/* Desc of the parameters:
	*	self:
	*		type: PyObject pointer
	*		reference: python inner object
	*	args:
	*		type: PyObject pointer
	*		reference: python inner object like the tuple type
	*					in order to transfer the parameters of the function to C language system
	*/

	// 声明一个Python对象(列表)
	PyObject* mylist;

	// list是一个Python对象
	if (!PyArg_ParseTuple(args, "O", &mylist))
		return NULL;

	// 检查是否是一个列表
	if (!PyList_Check(mylist))
		return NULL;

	// 获取长度
	Py_ssize_t list_len = PyList_Size(mylist);
	cout << "列表长度: " << list_len << endl;

	float item_double;
	PyObject* item_To_PyObj;

	for (Py_ssize_t index = 0; index < list_len; index++) {

		// 在Python中是mylist[isndex]中的形式获取元素，这里的做法一模一样
		PyObject* item = PyList_GetItem(mylist, index);

		item_double = PyFloat_AsDouble(item) + 100;

		// build a float
		item_To_PyObj = Py_BuildValue("f", item_double);

		// 元素获取失败
		if (!item) {
			cerr << "#list:[Error~0]" << endl;
			continue;
		}

		// 这里直接调用Python对象的魔法方法__str__获取这个类型本该输出的样子
		// PyObject* py_str = PyObject_Str(item);
		PyObject* py_str = PyObject_Str(item_To_PyObj);

		// 函数调用成功返回非NULL的地址
		if (py_str) {
			// 将字符串对象转换为C宽字符串
			wchar_t* wc_str = PyUnicode_AsWideCharString(py_str, NULL);
			if (wc_str) {
				// 输出宽字符串
				wcout << L"list~[" << index << "]: " << wc_str << endl;
				// 记得释放
				PyMem_Free(wc_str);
			}
			else {
				// 获取字符串出错！
				cerr << "#List:[Error~2]" << endl;
			}
			// 引用计数-1,表示本次获取到的字符串对象已经不用了
			Py_XDECREF(py_str);
		}
		else {
			// 执行对象__str__方法失败
			cerr << "#List:[Error~1]" << endl;
		}
	}

	// 返回列表长度
	return Py_BuildValue("i", list_len);
}

/*
* 遍历元组
*/
// 这里的做法跟元组的几乎无差别(直接是拷贝过来稍稍修改)
static PyObject* WalkingSequence_WalkingDownTuple(
	PyObject* self,
	PyObject* args
) {

	// 声明一个Python对象(元组)
	PyObject* mytuple;

	// tuple是一个Python对象
	if (!PyArg_ParseTuple(args, "O", &mytuple))
		return NULL;

	// 检查是否是一个元组
	if (!PyTuple_Check(mytuple))
		return NULL;

	// 获取长度
	Py_ssize_t tuple_len = PyTuple_Size(mytuple);
	cout << "元表长度: " << tuple_len << endl;

	for (Py_ssize_t index = 0; index < tuple_len; index++) {

		// 在Python中是mytuple[index]中的形式获取元素，这里的做法一模一样
		PyObject* item = PyTuple_GetItem(mytuple, index);

		// 元素获取失败
		if (!item) {
			cerr << "#tuple:[Error~0]" << endl;
			continue;
		}

		// 这里直接调用Python对象的魔法方法__str__获取这个类型本该输出的样子
		PyObject* py_str = PyObject_Str(item);

		// 函数调用成功返回非NULL的地址
		if (py_str) {
			// 将字符串对象转换为C宽字符串
			wchar_t* wc_str = PyUnicode_AsWideCharString(py_str, NULL);
			if (wc_str) {
				// 输出宽字符串
				wcout << L"tuple~[" << index << "]: " << wc_str << endl;
				// 记得释放
				PyMem_Free(wc_str);
			}
			else {
				// 获取字符串出错！
				cerr << "#tuple:[Error~2]" << endl;
			}
			// 引用计数-1,表示本次获取到的字符串对象已经不用了
			Py_XDECREF(py_str);
		}
		else {
			// 执行对象__str__方法失败
			cerr << "#tuple:[Error~1]" << endl;
		}
	}

	// 返回元组长度
	return Py_BuildValue("i", tuple_len);
}

/*
* 遍历字典
*/
static PyObject* WalkingSequence_WalkingDownDict(
	PyObject* self,
	PyObject* args
) {

	// 声明一个Python对象(字典)
	PyObject* mydict;

	// dict是一个Python对象
	if (!PyArg_ParseTuple(args, "O", &mydict))
		return NULL;

	// 检查是否是一个字典
	if (!PyDict_Check(mydict))
		return NULL;

	/* 字典是有限集,可以获取长度 */
	Py_ssize_t dict_len = PyDict_Size(mydict);
	cout << "字典内元素个数: " << endl;

	PyObject* key;
	PyObject* value;
	/* 开始前pos必须初始化为0 */
	Py_ssize_t pos = 0;

	// 遍历完返回0
	while (PyDict_Next(mydict, &pos, &key, &value)) {
		// 管他啥类型,直接调用其__str__魔法方法,返回它本来该输出的样子
		// 这里得注意的是,字典的键不一定是字符串
		PyObject* py_str_key = PyObject_Str(key);
		if (py_str_key) {
			wchar_t* wc_str_key = PyUnicode_AsWideCharString(py_str_key, NULL);
			if (wc_str_key) {
				// 输出键
				wcout << wc_str_key;
				PyMem_Free(wc_str_key);
			}
			else {
				cerr << "#dict:[Error~2]" << endl;
				Py_XDECREF(py_str_key);
				continue;
			}
			Py_XDECREF(py_str_key);
		}
		else {
			cerr << "#dict:[Error~1]" << endl;
			continue;
		}

		// 输出冒号
		cout.put(':');

		/* 下面的步骤和上面的一样 */
		PyObject* py_str_value = PyObject_Str(value);
		if (py_str_value) {
			wchar_t* wc_str_value = PyUnicode_AsWideCharString(py_str_value, NULL);
			if (wc_str_value) {
				// 输出值
				wcout << wc_str_value << endl;;
				PyMem_Free(wc_str_value);
			}
			else {
				cerr << "#dict:[Error~4]" << endl;
			}
			Py_XDECREF(py_str_value);
		}
		else {
			cerr << "#dict:[Error~3]" << endl;
			continue;
		}
	}


	// Long类型对应的是Python中的整数
	return PyLong_FromSsize_t(dict_len);
}

/*
* 遍历集合
*/
static PyObject* WalkingSequence_WalkingDownSet(
	PyObject* self,
	PyObject* args
) {

	// 声明一个Python对象(集合)
	PyObject* myset;

	// dict是一个Python对象
	if (!PyArg_ParseTuple(args, "O", &myset))
		return NULL;

	// 检查是否是一个字典
	if (!PySet_Check(myset))
		return NULL;

	// 集合性质三要素之一:有限性
	Py_ssize_t set_len = PySet_Size(myset);

	/*
	*	// 集合肯定是可迭代的啦....
	*	if (PyIter_Check(myset))
	*		return NULL;
	*/

	// 跟在python中用iter函数获取到一个迭代对象一样
	PyObject* myiterator = PyObject_GetIter(myset);

	PyObject* item;

	// 开始迭代,就类似于python中的myiterator = iter(myset);for item in myinterator: print(item)
	while ((item = PyIter_Next(myiterator)) != NULL) {
		PyObject* py_str = PyObject_Str(item);
		if (py_str) {
			wchar_t* wc_str = PyUnicode_AsWideCharString(py_str, NULL);
			if (wc_str) {
				wcout << wc_str << endl;
				PyMem_Free(wc_str);
			}
			else {
				cerr << "#set:[myiterator~2]" << endl;
			}
			Py_XDECREF(py_str);
		}
		else {
			cerr << "#set:[myiterator~1]" << endl;
		}
		// 注意这里！
		Py_XDECREF(item);
	}

	return PyLong_FromSsize_t(set_len);
}

/* Desc
*	At last
*		transfer the C functions to python
*
* Attention:
*	Python find the specific function
*		through a table
*/

// 这里直接用宏来解决
// 因为函数名太长，如果此函数没有文档，默认为NULL
#define WALKINGDOWNSEQUENCE_METHOD(name) {#name, WalkingSequence_##name, METH_VARARGS, NULL}

//格式{函数名字符串, 函数指针, 参数形式, 此函数/方法的文档(通过help函数获取)字符串}
//例如:{"WalkingDownList", WalkingSequence_WalkingDownList, METH_VARARGS, "这里是函数文档哟"}
/* 定义Python函数与C函数的映射表 */
static PyMethodDef WalkingSequenceMethods[] = {
	/* 下面的第一条与
	*	{"WalkingDownList",
	*	WalkingSequence_WalkingDownList,
	*	METH_VARARGS, NULL}
	*	等效
	*/
	WALKINGDOWNSEQUENCE_METHOD(WalkingDownList),
	WALKINGDOWNSEQUENCE_METHOD(WalkingDownTuple),
	WALKINGDOWNSEQUENCE_METHOD(WalkingDownDict),
	WALKINGDOWNSEQUENCE_METHOD(WalkingDownSet),
	{ NULL, NULL, 0, NULL }		//用全空的结构体成员元素作为结尾,也可以直接写{NULL},简洁
};


//文档就是可以通过help函数获取的字符串

/* 定义模块描述表(Python3.x必须定义) */
static PyModuleDef WalkingSequenceModule = {
	PyModuleDef_HEAD_INIT,  // 这个是必须加的
	"WalkingSequence",      // 模块的名字
	"Here\'s WalkingSequenceModule's document", // 模块文档
	-1,  // 给-1 默认，代表模块存在于全局表
	WalkingSequenceMethods, // 模块的函数映射表
	NULL, NULL, NULL, NULL  //  目前还不用对模块进行特殊处理，全部默认NULL
};


/* 这里非常关键,是导出C函数到Python的接口函数 */
/* 这里使用的是Python3.x的 c/api 函数导出接口格式,有别于Python2.x的 */
/* 接口函数格式 PyInit_+模块文件名 */
PyMODINIT_FUNC PyInit_WalkingSequence(void) {
	/* 创建模块并返回模块 */
	return PyModule_Create(&WalkingSequenceModule);
}
