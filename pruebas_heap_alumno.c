#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define TAM_ARREGLO 10
#define TEST_VOL 1000

int funcion_cmp(void* elem1,void* elem2){
  //Suponiendo que los elementos donde apuntan elem1 y elem2 son ints
  int a= *(int*)elem1;
  int b= *(int*)elem2;

  if(a==b) return 0;
  else if(a>b) return 1;
  else return -1;
}

void pruebas_vacio(){
  printf("\n\tINICIO PRUEBAS DE HEAP VACIO\n");
  heap_t* heap = heap_crear((cmp_func_t)funcion_cmp);
  print_test("Creo heap con funcion cmp, esta vacio",heap_esta_vacio(heap));
  print_test("Cantidad de elementos en el heap es 0",heap_cantidad(heap)==0);
  print_test("Ver max en heap vacio null",!heap_ver_max(heap));
  print_test("Desencolar heap vacio es NULL",!heap_desencolar(heap));
  print_test("Encolar NULL es false",!heap_encolar(heap,NULL));
  heap_destruir(heap,NULL);
}

void pruebas_basicas(){
  printf("\n\tINICIO PRUEBAS BASICAS DE HEAP\n");
  heap_t* heap=heap_crear((cmp_func_t)funcion_cmp);
  int a=9,b=7,c=11,d=5,e=17,f=1,g=21;

  print_test("Creo heap vacio",heap_esta_vacio(heap));
  print_test("Elementos es 0",heap_cantidad(heap)==0);
  print_test("Encolo a",heap_encolar(heap,&a));
  print_test("Ver max es a",heap_ver_max(heap)==&a);
  print_test("Encolo b",heap_encolar(heap,&b));
  print_test("Ver max sigue siendo a",heap_ver_max(heap)==&a);
  print_test("Cantidad de elementos es 2",heap_cantidad(heap)==2);
  print_test("Encolo c",heap_encolar(heap,&c));
  print_test("C>A entonces ver max ahora es c",heap_ver_max(heap)==&c);
  print_test("Cantidad de elementos es 3",heap_cantidad(heap)==3);
  print_test("Encolo d",heap_encolar(heap,&d));
  print_test("Cantidad de elementos es 4",heap_cantidad(heap)==4);
  print_test("Encolo e",heap_encolar(heap,&e));
  print_test("Cantidad de elementos es 5",heap_cantidad(heap)==5);
  print_test("E>C Ver max ahora es E",heap_ver_max(heap)==&e);
  print_test("Encolo f",heap_encolar(heap,&f));
  print_test("Cantidad de elementos es 6",heap_cantidad(heap)==6);
  print_test("Encolo g",heap_encolar(heap,&g));
  print_test("Cantidad de elementos es 7",heap_cantidad(heap)==7);
  print_test("G>E Ver max ahora es G",heap_ver_max(heap)==&g);
  print_test("DESENCOLO G",heap_desencolar(heap)==&g);
  print_test("cantidad de elementos es 6",heap_cantidad(heap)==6);
  print_test("DESENCOLO E",heap_desencolar(heap)==&e);
  print_test("cantidad de elementos es 5",heap_cantidad(heap)==5);
  print_test("DESENCOLO C",heap_desencolar(heap)==&c);
  print_test("cantidad de elementos es 4",heap_cantidad(heap)==4);
  print_test("DESENCOLO A",heap_desencolar(heap)==&a);
  print_test("cantidad de elementos es 3",heap_cantidad(heap)==3);
  print_test("DESENCOLO B",heap_desencolar(heap)==&b);
  print_test("cantidad de elementos es 2",heap_cantidad(heap)==2);
  heap_destruir(heap,NULL);

}

void pruebas_heap_crear_arr(){
  printf("\n\tINICIO PRUEBAS DE HEAP_CREAR_ARR\n");
  int array1[TAM_ARREGLO]={16,14,10,9,8,7,5,3,2,1}; //array inversamente ordenado
  int array2[TAM_ARREGLO]={1,2,3,5,7,9,11,12,15,17}; //array ordenado
  int array3[TAM_ARREGLO]; //array aleatorio

  srand (time(NULL));
  for (int i=0; i<TAM_ARREGLO; i++){
    int aleatorio = rand()%200;
    array3[i] = aleatorio;
  }

  void* p_array1[TAM_ARREGLO]; void* p_array2[TAM_ARREGLO]; void* p_array3[TAM_ARREGLO];
  for(size_t i=0;i<TAM_ARREGLO;i++){
    p_array1[i] = &array1[i];
    p_array2[i] = &array2[i];
    p_array3[i] = &array3[i];
  }

  heap_t* heap1= heap_crear_arr(p_array1,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  heap_t* heap2= heap_crear_arr(p_array2,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  heap_t* heap3= heap_crear_arr(p_array3,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  
  print_test("Heap1 con crear_arr no esta vacio",!heap_esta_vacio(heap1));
  print_test("Heap2 con crear_arr no esta vacio",!heap_esta_vacio(heap2));
  print_test("Heap3 con crear_arr no esta vacio",!heap_esta_vacio(heap3));
  print_test("Heap1 cantidad es TAM_ARREGLO",heap_cantidad(heap1)==TAM_ARREGLO);
  print_test("Heap2 cantidad es TAM_ARREGLO",heap_cantidad(heap1)==TAM_ARREGLO);
  print_test("Heap3 cantidad es TAM_ARREGLO",heap_cantidad(heap1)==TAM_ARREGLO);

  bool ok1 = true; int desencolado1; int primero1;
  bool ok2 = true; int desencolado2; int primero2;
  bool ok3 = true; int desencolado3; int primero3;

  for (int i = 0; i<TAM_ARREGLO - 1; i++){
    desencolado1 = *(int*)heap_desencolar(heap1);
    primero1 = *(int*)heap_ver_max(heap1);
    ok1 &= (desencolado1 >= primero1);
  
    desencolado2 = *(int*)heap_desencolar(heap2);
    primero2 = *(int*)heap_ver_max(heap2);
    ok2 &= (desencolado2 >= primero2);

    desencolado3 = *(int*)heap_desencolar(heap3);
    primero3 = *(int*)heap_ver_max(heap3);
    ok3 &= (desencolado3 >= primero3);
  }

  print_test("Heap1 desencolado en orden", ok1);
  print_test("Heap2 desencolado en orden", ok2);
  print_test("Heap3 desencolado en orden", ok3);
  heap_destruir(heap1,NULL); 
  heap_destruir(heap2,NULL);
  heap_destruir(heap3,NULL);
}

void pruebas_heapsort(){
  printf("\n\tINICIO PRUEBAS DE HEAPSORT\n");
  int array1[TAM_ARREGLO]={46,40,30,24,17,16,12,3,2,1}; //array inversamente ordenado
  int array2[TAM_ARREGLO]={1,2,3,14,25,26,37,38,50}; //array ordenado
  int array3[TAM_ARREGLO]; //array aleatorio

  srand (time(NULL));
  for (int i=0; i<TAM_ARREGLO; i++){
    int aleatorio = rand()%200;
    array3[i] = aleatorio;
  }  

  void* p_array1[TAM_ARREGLO]; void* p_array2[TAM_ARREGLO]; void* p_array3[TAM_ARREGLO];
  for(size_t i=0;i<TAM_ARREGLO;i++){
    p_array1[i] = &array1[i];
    p_array2[i] = &array2[i];
    p_array3[i] = &array3[i];
  }

  heap_sort(p_array1,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  heap_sort(p_array2,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  heap_sort(p_array3,TAM_ARREGLO,(cmp_func_t)funcion_cmp);
  
  bool ok1 = true; bool ok2 = true; bool ok3 = true;
  for (int i = 0; i<TAM_ARREGLO - 1; i++){
    ok1 &= *(int*)p_array1[i] <= *(int*)p_array1 [i + 1];
    ok2 &= *(int*)p_array2[i] <= *(int*)p_array2 [i + 1];
    ok3 &= *(int*)p_array3[i] <= *(int*)p_array3 [i + 1];
  }

 
  print_test("Heapsort ordeno el arreglo inversamente ordenado", ok1);
  print_test("Heapsort ordeno el arreglo ordenado", ok2);
  print_test("Heapsort ordeno el arreglo aleatorio", ok3);

}

void pruebas_destruir(){
  printf("\n\tINICIO PRUEBAS CON DESTRUIR\n");
  heap_t* heap = heap_crear((cmp_func_t)funcion_cmp);
  
  bool ok = true;
  srand (time(NULL));
  for (int i=0; i<TAM_ARREGLO; i++){
    int* aleatorio = malloc(sizeof(int));
    *aleatorio = rand()%200;
    ok &= heap_encolar(heap,aleatorio);
  }

  print_test("Se encolaron todos los elementos", ok);
  
  heap_destruir(heap,free);
  
}
void pruebas_volumen_heap(size_t cantidad_elementos){
  printf("\n\tINICIO PRUEBAS DE VOLUMEN DE HEAP\n");
  heap_t* heap = heap_crear((cmp_func_t)funcion_cmp);
  bool ok = true;
  srand (time(NULL));
  for (int i=0; i<cantidad_elementos; i++){
    int aleatorio = rand();
    ok &= heap_encolar(heap,&aleatorio);
  }
  print_test("Todos los valores encolados", ok);
  print_test("Cantidad de elementos es TEST_VOL", heap_cantidad(heap) == cantidad_elementos);

  int desencolado; int primero;

  for (int i=0; i<cantidad_elementos - 1; i++){
    desencolado = *(int*)heap_desencolar(heap);
    primero = *(int*)heap_ver_max(heap);
    ok &= (desencolado >= primero);
  }
  heap_desencolar(heap);
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Desencolados en orden", ok);
  heap_destruir(heap,NULL);
}

void pruebas_heap_alumno(){
  pruebas_vacio();
  pruebas_basicas();
  pruebas_heap_crear_arr();
  pruebas_heapsort();
  pruebas_destruir();
  pruebas_volumen_heap(TEST_VOL);
}

