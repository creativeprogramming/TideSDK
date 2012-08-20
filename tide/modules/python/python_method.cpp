/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include "python_method.h"

namespace tide
{
	KPythonMethod::KPythonMethod(PyObject *method) :
		Method("Python.Method"),
		method(method),
		object(new KPythonObject(method))
	{
		PyLockGIL lock;
		Py_INCREF(this->method);
	}

	KPythonMethod::~KPythonMethod()
	{
		PyLockGIL lock;
		Py_DECREF(this->method);
	}

	ValueRef KPythonMethod::Call(const ValueList& args)
	{
		PyLockGIL lock;
		PyObject *arglist = NULL;

		if (args.size() > 0)
		{
			arglist = PyTuple_New(args.size());
			for (size_t i = 0; i < args.size(); i++)
			{
				PyObject *pv = PythonUtils::ToPyObject(args[i]);
				PyTuple_SetItem(arglist, i, pv);
			}
		}

		PyObject *response = PyObject_CallObject(this->method, arglist);
		Py_XDECREF(arglist);

		ValueRef value = Value::Undefined;
		if (response == NULL && PyErr_Occurred() != NULL)
		{
			THROW_PYTHON_EXCEPTION
		}
		else if (response != NULL)
		{
			value = PythonUtils::ToTideValue(response);
			Py_DECREF(response);
		}

		return value;
	}

	void KPythonMethod::Set(const char *name, ValueRef value)
	{
		this->object->Set(name, value);
	}

	ValueRef KPythonMethod::Get(const char *name)
	{
		return this->object->Get(name);
	}

	SharedStringList KPythonMethod::GetPropertyNames()
	{
		return this->object->GetPropertyNames();
	}

	PyObject* KPythonMethod::ToPython()
	{
		return this->object->ToPython();
	}

	bool KPythonMethod::Equals(ObjectRef other)
	{
		AutoPtr<KPythonMethod> pyOther = other.cast<KPythonMethod>();

		// This is not a Python object
		if (pyOther.isNull())
			return false;

		return pyOther->ToPython() == this->ToPython();
	}

}