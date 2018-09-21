#include "newdelete.hpp"
#include <new>

#include <iostream>
/* Here we redefine operator new and delete, so 3rd party libraries using them
   that also call gmp, which in turn calls libgc, will
   not have libgc regard their gmp integers as garbage and collect them */
/* Nevertheless, in our code we prefer to use the classes defined below, one of
 * which offers the use of GC_MALLOC_ATOMIC() */
/* The static inline versions are defined in newdelete.hpp */
void* operator new(size_t size)
{
  // std::cout << "calling new on size " << size << std::endl;
  TRAPCHK_SIZE(size);
  void* p = GC_MALLOC_UNCOLLECTABLE(size);
  if (p == NULL) outofmem2(size);
  TRAPCHK(p);
  return p;
}
void* operator new[](size_t size)
{
  // std::cout << "calling new[] on size " << size << std::endl;
  TRAPCHK_SIZE(size);
  void* p = GC_MALLOC_UNCOLLECTABLE(size);
  if (p == NULL) outofmem2(size);
  TRAPCHK(p);
  return p;
}
void* operator new(size_t size, const std::nothrow_t& t) noexcept
{
  // std::cout << "calling new nothrow on size " << size << std::endl;
  TRAPCHK_SIZE(size);
  void* p = GC_MALLOC_UNCOLLECTABLE(size);
  if (p == NULL) outofmem2(size);
  TRAPCHK(p);
  return p;
}
void* operator new[](size_t size, const std::nothrow_t& t) noexcept
{
  // std::cout << "calling new[] nothrow on size " << size << std::endl;
  TRAPCHK_SIZE(size);
  void* p = GC_MALLOC_UNCOLLECTABLE(size);
  if (p == NULL) outofmem2(size);
  TRAPCHK(p);
  return p;
}

void operator delete(void* obj) noexcept
{
  TRAPCHK(obj);
  if (obj != NULL) GC_FREE(obj);
}
void operator delete[](void* obj) noexcept
{
  TRAPCHK(obj);
  if (obj != NULL) GC_FREE(obj);
}
void operator delete(void* obj, const std::nothrow_t& t) noexcept
{
  TRAPCHK(obj);
  if (obj != NULL) GC_FREE(obj);
}
void operator delete[](void* obj, const std::nothrow_t& t) noexcept
{
  TRAPCHK(obj);
  if (obj != NULL) GC_FREE(obj);
}

#if 0

    This is from /usr/include/c++/4.2.1/new :

    void* operator new(std::size_t) throw (std::bad_alloc);
    void* operator new[](std::size_t) throw (std::bad_alloc);
    void* operator new(std::size_t, const std::nothrow_t&) throw();
    void* operator new[](std::size_t, const std::nothrow_t&) throw();
    inline void* operator new(std::size_t, void* __p) throw() { return __p; }
    inline void* operator new[](std::size_t, void* __p) throw() { return __p; }

    void operator delete(void*) throw();
    void operator delete[](void*) throw();
    void operator delete(void*, const std::nothrow_t&) throw();
    void operator delete[](void*, const std::nothrow_t&) throw();
    inline void  operator delete  (void*, void*) throw() { }
    inline void  operator delete[](void*, void*) throw() { }

#endif

/*
 Local Variables:
 compile-command: "make -C $M2BUILDDIR/Macaulay2/e newdelete.o "
 End:
*/
