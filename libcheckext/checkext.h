#ifndef _checkext_h_
#define _checkext_h_


#include <math.h>  /* Needed for fabs() */


#ifdef __cplusplus
extern "C" {
#endif



/*
 * "Check" extensions for floats:
 */

#define ck_assert_flt_eq(X, Y) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = 1e-6f; \
    ck_assert_msg(fabs(_ck_x - _ck_y) <= _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" == "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define ck_assert_flt_ne(X, Y) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = 1e-6f; \
    ck_assert_msg(fabs(_ck_x - _ck_y) > _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" != "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define _ck_assert_flt_ineq_lt(X, OP, Y) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = 1e-6f; \
    ck_assert_msg(_ck_x OP _ck_y + _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define _ck_assert_flt_ineq_gt(X, OP, Y) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = 1e-6f; \
    ck_assert_msg(_ck_x OP _ck_y - _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define ck_assert_flt_lt(X, Y) _ck_assert_flt_ineq_lt(X, <, Y)
#define ck_assert_flt_le(X, Y) _ck_assert_flt_ineq_lt(X, <=, Y)
#define ck_assert_flt_gt(X, Y) _ck_assert_flt_ineq_gt(X, >, Y)
#define ck_assert_flt_ge(X, Y) _ck_assert_flt_ineq_gt(X, >=, Y)



/*
 * "Check" extensions for floats with eps:
 */

#define ck_assert_flt_eq_eps(X, Y, eps) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = (eps); \
    ck_assert_msg(fabs(_ck_x - _ck_y) <= _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" == "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define ck_assert_flt_ne_eps(X, Y, eps) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = (eps); \
    ck_assert_msg(fabs(_ck_x - _ck_y) > _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" != "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define _ck_assert_flt_ineq_lt_eps(X, OP, Y, eps) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = (eps); \
    ck_assert_msg(_ck_x OP _ck_y + _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define _ck_assert_flt_ineq_gt_eps(X, OP, Y, eps) do { \
    float _ck_x = (X); \
    float _ck_y = (Y); \
    float _eps = (eps); \
    ck_assert_msg(_ck_x OP _ck_y - _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define ck_assert_flt_lt_eps(X, Y, eps) _ck_assert_flt_ineq_lt_eps(X, <, Y, eps)
#define ck_assert_flt_le_eps(X, Y, eps) _ck_assert_flt_ineq_lt_eps(X, <=, Y, eps)
#define ck_assert_flt_gt_eps(X, Y, eps) _ck_assert_flt_ineq_gt_eps(X, >, Y, eps)
#define ck_assert_flt_ge_eps(X, Y, eps) _ck_assert_flt_ineq_gt_eps(X, >=, Y, eps)



/*
 * "Check" extensions for doubles:
 */

#define ck_assert_dbl_eq(X, Y) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = 1e-6; \
    ck_assert_msg(fabs(_ck_x - _ck_y) <= _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" == "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define ck_assert_dbl_ne(X, Y) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = 1e-6; \
    ck_assert_msg(fabs(_ck_x - _ck_y) > _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" != "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define _ck_assert_dbl_ineq_lt(X, OP, Y) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = 1e-6; \
    ck_assert_msg(_ck_x OP _ck_y + _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define _ck_assert_dbl_ineq_gt(X, OP, Y) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = 1e-6; \
    ck_assert_msg(_ck_x OP _ck_y - _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, eps == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, _eps); \
} while (0)

#define ck_assert_dbl_lt(X, Y) _ck_assert_dbl_ineq_lt(X, <, Y)
#define ck_assert_dbl_le(X, Y) _ck_assert_dbl_ineq_lt(X, <=, Y)
#define ck_assert_dbl_gt(X, Y) _ck_assert_dbl_ineq_gt(X, >, Y)
#define ck_assert_dbl_ge(X, Y) _ck_assert_dbl_ineq_gt(X, >=, Y)



/*
 * "Check" extensions for doubles with eps:
 */

#define ck_assert_dbl_eq_eps(X, Y, eps) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = (eps); \
    ck_assert_msg(fabs(_ck_x - _ck_y) <= _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" == "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define ck_assert_dbl_ne_eps(X, Y, eps) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = (eps); \
    ck_assert_msg(fabs(_ck_x - _ck_y) > _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" != "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define _ck_assert_dbl_ineq_lt_eps(X, OP, Y, eps) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = (eps); \
    ck_assert_msg(_ck_x OP _ck_y + _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define _ck_assert_dbl_ineq_gt_eps(X, OP, Y, eps) do { \
    double _ck_x = (X); \
    double _ck_y = (Y); \
    double _eps = (eps); \
    ck_assert_msg(_ck_x OP _ck_y - _eps, \
        "Assertion '%s' failed: %s == %.7g, %s == %.7g, %s == %.7g", #X" "#OP" "#Y, #X, _ck_x, #Y, _ck_y, #eps, _eps); \
} while (0)

#define ck_assert_dbl_lt_eps(X, Y, eps) _ck_assert_dbl_ineq_lt_eps(X, <, Y, eps)
#define ck_assert_dbl_le_eps(X, Y, eps) _ck_assert_dbl_ineq_lt_eps(X, <=, Y, eps)
#define ck_assert_dbl_gt_eps(X, Y, eps) _ck_assert_dbl_ineq_gt_eps(X, >, Y, eps)
#define ck_assert_dbl_ge_eps(X, Y, eps) _ck_assert_dbl_ineq_gt_eps(X, >=, Y, eps)



#ifdef __cplusplus
}
#endif


#endif
