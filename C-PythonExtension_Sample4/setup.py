# encoding=utf-8
# Date: 2018-12-29


from distutils.core import setup, Extension

#模块名
MOD = 'WalkingSequence'
setup(name=MOD,ext_modules=[Extension(MOD,sources=['D:\\USBei\\C++Projects\\C++PythonExtension_Sample4\\C++PythonExtension_Sample4\\WalkingSequence.cpp'])])


"""
	cmd commands records:
	
		python D:\\USBei\\C++Projects\\C++PythonExtension_Sample4\\C++PythonExtension_Sample4\\setup.py build
		python D:\\USBei\\C++Projects\\C++PythonExtension_Sample4\\C++PythonExtension_Sample4\\setup.py install
		
	cmd python console commands records:

		>>> import WalkingSequence
		>>> dir(WalkingSequence)
		['WalkingDownDict', 'WalkingDownList', 'WalkingDownSet', 'WalkingDownTuple', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__']
		>>> help(WalkingSequence)
		Help on module WalkingSequence:

		NAME
			WalkingSequence - Here's WalkingSequenceModule's document

		FUNCTIONS
			WalkingDownDict(...)

			WalkingDownList(...)

			WalkingDownSet(...)

			WalkingDownTuple(...)

		FILE
			c:\python35\lib\site-packages\walkingsequence.cp35-win_amd64.pyd

		>>> WalkingSequence.WalkingDownList([1, 2, 3])
		列表长度: 3
		l i s t ~ [ 0 ] :   1 0 1 . 0
		 l i s t ~ [ 1 ] :   1 0 2 . 0
		 l i s t ~ [ 2 ] :   1 0 3 . 0
		 3

		>>> WalkingSequence.WalkingDownTuple((1, 2, 3))
		元表长度: 3
		t u p l e ~ [ 0 ] :   1
		 t u p l e ~ [ 1 ] :   2
		 t u p l e ~ [ 2 ] :   3
		 3
		 
		>>> WalkingSequence.WalkingDownSet({1, 2, 3})
		1
		 2
		 3
		 3
		 
		 >>> WalkingSequence.WalkingDownDict(dict(a=1, b=2, c=3))
		字典内元素个数:
		a :1
		 b :2
		 c :3
		 3
		>>>
"""
