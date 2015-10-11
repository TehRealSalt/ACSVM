//-----------------------------------------------------------------------------
//
// Copyright (C) 2015 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Vector class.
//
//-----------------------------------------------------------------------------

#ifndef ACSVM__Vector_H__
#define ACSVM__Vector_H__

#include "Types.hpp"

#include <new>


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace ACSVM
{
   //
   // Vector
   //
   // Runtime sized array.
   //
   template<typename T>
   class Vector
   {
   public:
      using iterator  = T *;
      using size_type = std::size_t;


      Vector() : dataV{nullptr}, dataC{0} {}
      ~Vector() {free();}

      T &operator [] (size_type i) {return dataV[i];}

      //
      // alloc
      //
      template<typename... Args>
      void alloc(size_type count, Args const &...args)
      {
         if(dataV) free();

         dataC = count;
         dataV = static_cast<T *>(::operator new(sizeof(T) * dataC));

         for(T *itr = dataV, *end = itr + dataC; itr != end; ++itr)
            new(itr) T{args...};
      }

      iterator begin() {return dataV;}

      T *data() {return dataV;}

      iterator end() {return dataV + dataC;}

      //
      // free
      //
      void free()
      {
         if(!dataV) return;

         for(T *itr = dataV + dataC; itr != dataV;)
            (--itr)->~T();

         ::operator delete(dataV);
         dataV = nullptr;
         dataC = 0;
      }

      size_type size() const {return dataC;}

   private:
      T        *dataV;
      size_type dataC;
   };
}

#endif//ACSVM__Vector_H__

