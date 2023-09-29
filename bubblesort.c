#include <Python.h>

static void bubblesort(int array[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

static PyObject *bubble_sort(PyObject *self, PyObject *args) {
  PyObject *py_list;

  if (!PyArg_ParseTuple(args, "O", &py_list)) {
    return NULL;
  }

  if (!PyList_Check(py_list)) {
    PyErr_SetString(PyExc_TypeError, "Input must be a list.");
    return NULL;
  }

  int list_size = PyList_Size(py_list);
  int *arr = malloc(list_size * sizeof(int));

  if (arr == NULL) {
    PyErr_SetString(PyExc_MemoryError, "Memory allocation failed.");
    return NULL;
  }

  for (int i = 0; i < list_size; i++) {
    PyObject *item = PyList_GetItem(py_list, i);
    arr[i] = PyLong_AsLong(item);
  }

  bubblesort(arr, list_size);

  PyObject *result_list = PyList_New(list_size);

  if (result_list == NULL) {
    free(arr);
    PyErr_SetString(PyExc_MemoryError, "Memory allocation failed.");
    return NULL;
  }

  for (int i = 0; i < list_size; i++) {
    PyObject *item = PyLong_FromLong(arr[i]);
    PyList_SetItem(result_list, i, item);
  }

  free(arr);
  return result_list;
}

static PyMethodDef methods[] = {
    {"bubble_sort", bubble_sort, METH_VARARGS,
     "Sorts a list using the bubble sort algorithm."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef bubblesortmodule = {
    PyModuleDef_HEAD_INIT, "bubblesortmodule", NULL, -1, methods};

PyMODINIT_FUNC PyInit_bubblesortmodule(void) {
  return PyModule_Create(&bubblesortmodule);
}
