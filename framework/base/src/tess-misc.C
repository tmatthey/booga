/*
 * tess-misc.h
 *
 * This code is in the public domain. Specifically, we give to the public
 * domain all rights for future licensing of the source code, all resale
 * rights, and all publishing rights.
 * 
 * UNC-CH GIVES NO WARRANTY, EXPRESSED OR IMPLIED, FOR THE SOFTWARE
 * AND/OR DOCUMENTATION PROVIDED, INCLUDING, WITHOUT LIMITATION, WARRANTY
 * OF MERCHANTABILITY AND WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE.
 *
 *                            - Atul Narkhede (narkhede@cs.unc.edu), 1995
 *
 * Orginal source code:
 *   ftp://ftp.cs.unc.edu/pub/users/narkhede/triangulation.tar.gz
 *
 * Reference:
 *   R. Seidel, 
 *   A simple and Fast Randomized Algorithm for Computing Trapezoidal 
 *   Decompositions and for Triangulating Polygons,
 *   Computational Geometry Theory & Applications, 1991.
 *
 * -----------------------------------------------------------------------------
 *  $Id: tess-misc.C,v 1.2 1997/09/19 07:14:56 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif
#include <math.h>
#include "tess-triangulate.h"
#include "booga/base/mathutilities.h"
static int choose_idx;
static int permute[SEGSIZE];

#ifdef WIN32
inline double log2(double x)
{
  return log(x)/M_LN2;
}
#endif

/* Generate a random permutation of the segments 1..n */
int generate_random_ordering(int n)
{
#ifndef WIN32
  struct timeval tval;
  struct timezone tzone;
#endif
  register int i;
  int m, st[SEGSIZE], *p;
  
  choose_idx = 1;
#ifndef WIN32
  gettimeofday(&tval, &tzone);
  srand48(tval.tv_sec);
#else
  time_t ltime;
  time(&ltime);
  srand(ltime);
#endif
  for (i = 0; i <= n; i++)
    st[i] = i;

  p = st;
  for (i = 1; i <= n; i++, p++)
    {
#ifndef WIN32
      m = lrand48() % (n + 1 - i) + 1;
#else
	  m = rand() % (n + 1 - i) + 1;
#endif
      permute[i] = p[m];
      if (m != 1)
	p[m] = p[1];
    }
  return 0;
}

  
/* Return the next segment in the generated random ordering of all the */
/* segments in S */
int choose_segment()
{
  return permute[choose_idx++];
}


/* Get log*n for given n */
int math_logstar_n(int n)
{
  register int i;
  double v;
  
  for (i = 0, v = (double) n; v >= 1; i++)
    v = log2(v);
  
  return (i - 1);
}
  

int math_N(int n, int h)
{
  register int i;
  double v;

  for (i = 0, v = (int) n; i < h; i++)
    v = log2(v);
  
  return (int) ceil((double) 1.0*n/v);
}
