/**
 * @file lv_draw_vector.h
 *
 */

#ifndef LV_DRAW_VECTOR_H
#define LV_DRAW_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_array.h"
#include "../misc/lv_matrix.h"
#include "lv_draw_image.h"

#if LV_USE_VECTOR_GRAPHIC

#if !LV_USE_MATRIX
#error "lv_draw_vector needs LV_USE_MATRIX = 1"
#endif

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    LV_VECTOR_FILL_NONZERO = 0,
    LV_VECTOR_FILL_EVENODD,
} lv_vector_fill_t;

typedef enum {
    LV_VECTOR_STROKE_CAP_BUTT = 0,
    LV_VECTOR_STROKE_CAP_SQUARE,
    LV_VECTOR_STROKE_CAP_ROUND,
} lv_vector_stroke_cap_t;

typedef enum {
    LV_VECTOR_STROKE_JOIN_MITER = 0,
    LV_VECTOR_STROKE_JOIN_BEVEL,
    LV_VECTOR_STROKE_JOIN_ROUND,
} lv_vector_stroke_join_t;

typedef enum {
    LV_VECTOR_PATH_QUALITY_MEDIUM = 0, /* default*/
    LV_VECTOR_PATH_QUALITY_HIGH,
    LV_VECTOR_PATH_QUALITY_LOW,
} lv_vector_path_quality_t;

typedef enum {
    LV_VECTOR_BLEND_SRC_OVER = 0,
    LV_VECTOR_BLEND_SRC_IN,
    LV_VECTOR_BLEND_DST_OVER,
    LV_VECTOR_BLEND_DST_IN,
    LV_VECTOR_BLEND_SCREEN,
    LV_VECTOR_BLEND_MULTIPLY,
    LV_VECTOR_BLEND_NONE,
    LV_VECTOR_BLEND_ADDITIVE,
    LV_VECTOR_BLEND_SUBTRACTIVE,
} lv_vector_blend_t;

typedef enum {
    LV_VECTOR_PATH_OP_MOVE_TO = 0,
    LV_VECTOR_PATH_OP_LINE_TO,
    LV_VECTOR_PATH_OP_QUAD_TO,
    LV_VECTOR_PATH_OP_CUBIC_TO,
    LV_VECTOR_PATH_OP_CLOSE,
} lv_vector_path_op_t;

typedef enum {
    LV_VECTOR_DRAW_STYLE_SOLID = 0,
    LV_VECTOR_DRAW_STYLE_PATTERN,
    LV_VECTOR_DRAW_STYLE_GRADIENT,
} lv_vector_draw_style_t;

typedef enum {
    LV_VECTOR_GRADIENT_SPREAD_PAD = 0,
    LV_VECTOR_GRADIENT_SPREAD_REPEAT,
    LV_VECTOR_GRADIENT_SPREAD_REFLECT,
} lv_vector_gradient_spread_t;

typedef enum {
    LV_VECTOR_GRADIENT_STYLE_LINEAR = 0,
    LV_VECTOR_GRADIENT_STYLE_RADIAL,
} lv_vector_gradient_style_t;

typedef enum {
    LV_VECTOR_FILL_UNITS_OBJECT_BOUNDING_BOX = 0, /** Relative coordinates relative to the object bounding box. */
    LV_VECTOR_FILL_UNITS_USER_SPACE_ON_USE, /** Absolute coordinates relative to the layer's coordinate system */
} lv_vector_fill_units_t;

struct _lv_fpoint_t {
    float x;
    float y;
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Transform the coordinates of a point using given matrix
 * @param matrix           pointer to a matrix
 * @param point            pointer to a point
 */
void lv_matrix_transform_point(const lv_matrix_t * matrix, lv_fpoint_t * point);

/**
 * Transform all the coordinates of a path using given matrix
 * @param matrix           pointer to a matrix
 * @param path             pointer to a path
 */
void lv_matrix_transform_path(const lv_matrix_t * matrix, lv_vector_path_t * path);

/**
 * Create a vector graphic path object
 * @param quality       the quality hint of path
 * @return              pointer to the created path object
 */
lv_vector_path_t * lv_vector_path_create(lv_vector_path_quality_t quality);

/**
 * Copy a path data to another
 * @param target_path       pointer to a path
 * @param path              pointer to source path
 */
void lv_vector_path_copy(lv_vector_path_t * target_path, const lv_vector_path_t * path);

/**
 * Clear path data
 * @param path              pointer to a path
 */
void lv_vector_path_clear(lv_vector_path_t * path);

/**
 * Delete the graphic path object
 * @param path              pointer to a path
 */
void lv_vector_path_delete(lv_vector_path_t * path);

/**
 * Begin a new sub path and set a point to path
 * @param path              pointer to a path
 * @param p                 pointer to a `lv_fpoint_t` variable
 */
void lv_vector_path_move_to(lv_vector_path_t * path, const lv_fpoint_t * p);

/**
 * Add a line to the path from last point to the point
 * @param path              pointer to a path
 * @param p                 pointer to a `lv_fpoint_t` variable
 */
void lv_vector_path_line_to(lv_vector_path_t * path, const lv_fpoint_t * p);

/**
 * Add a quadratic bezier line to the path from last point to the point
 * @param path              pointer to a path
 * @param p1                pointer to a `lv_fpoint_t` variable for control point
 * @param p2                pointer to a `lv_fpoint_t` variable for end point
 */
void lv_vector_path_quad_to(lv_vector_path_t * path, const lv_fpoint_t * p1, const lv_fpoint_t * p2);

/**
 * Add a cubic bezier line to the path from last point to the point
 * @param path              pointer to a path
 * @param p1                pointer to a `lv_fpoint_t` variable for first control point
 * @param p2                pointer to a `lv_fpoint_t` variable for second control point
 * @param p3                pointer to a `lv_fpoint_t` variable for end point
 */
void lv_vector_path_cubic_to(lv_vector_path_t * path, const lv_fpoint_t * p1, const lv_fpoint_t * p2,
                             const lv_fpoint_t * p3);

/**
 * Add ellipse arc to the path from last point to the point
 * @param path              pointer to a path
 * @param radius_x          the x radius for ellipse arc
 * @param radius_y          the y radius for ellipse arc
 * @param rotate_angle      the rotate angle for arc
 * @param large_arc         true for large arc, otherwise small
 * @param clockwise         true for clockwise, otherwise anticlockwise
 * @param p                 pointer to a `lv_fpoint_t` variable for end point
 */
void lv_vector_path_arc_to(lv_vector_path_t * path, float radius_x, float radius_y, float rotate_angle, bool large_arc,
                           bool clockwise, const lv_fpoint_t * p);

/**
 * Close the sub path
 * @param path              pointer to a path
 */
void lv_vector_path_close(lv_vector_path_t * path);

/**
 * Get the bounding box of a path
 * @param path              pointer to a path
 * @param area              pointer to a `lv_area_t` variable for bounding box
 */
void lv_vector_path_get_bounding(const lv_vector_path_t * path, lv_area_t * area);

/**
 * Add a rectangle to the path
 * @param path              pointer to a path
 * @param rect              pointer to a `lv_area_t` variable
 * @param rx                the horizontal radius for rounded rectangle
 * @param ry                the vertical radius for rounded rectangle
 */
void lv_vector_path_append_rect(lv_vector_path_t * path, const lv_area_t * rect, float rx, float ry);

/**
 * Add a circle to the path
 * @param path              pointer to a path
 * @param c                 pointer to a `lv_fpoint_t` variable for center of the circle
 * @param rx                the horizontal radius for circle
 * @param ry                the vertical radius for circle
 */
void lv_vector_path_append_circle(lv_vector_path_t * path, const lv_fpoint_t * c, float rx, float ry);

/**
 * Add a arc to the path
 * @param path              pointer to a path
 * @param c                 pointer to a `lv_fpoint_t` variable for center of the circle
 * @param radius            the radius for arc
 * @param start_angle       the start angle for arc
 * @param sweep             the sweep angle for arc, could be negative
 * @param pie               true: draw a pie, false: draw a arc
 */
void lv_vector_path_append_arc(lv_vector_path_t * path, const lv_fpoint_t * c, float radius, float start_angle,
                               float sweep, bool pie);

/**
 * Add an sub path to the path
 * @param path              pointer to a path
 * @param subpath           pointer to another path which will be added
 */
void lv_vector_path_append_path(lv_vector_path_t * path, const lv_vector_path_t * subpath);

/**
 * Create a vector graphic descriptor
 * @param layer         pointer to a layer
 * @return              pointer to the created descriptor
 */
lv_vector_dsc_t * lv_vector_dsc_create(lv_layer_t * layer);

/**
 * Delete the vector graphic descriptor
 * @param dsc              pointer to a vector graphic descriptor
 */
void lv_vector_dsc_delete(lv_vector_dsc_t * dsc);

/**
 * Set a matrix to current transformation matrix
 * @param dsc              pointer to a vector graphic descriptor
 * @param matrix           pointer to a matrix
 */
void lv_vector_dsc_set_transform(lv_vector_dsc_t * dsc, const lv_matrix_t * matrix);

/**
 * Set blend mode for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param blend            the blend mode to be set in `lv_vector_blend_t`
 */
void lv_vector_dsc_set_blend_mode(lv_vector_dsc_t * dsc, lv_vector_blend_t blend);

/**
 * Set fill color for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param color            the color to be set in lv_color32_t format
 */
void lv_vector_dsc_set_fill_color32(lv_vector_dsc_t * dsc, lv_color32_t color);

/**
 * Set fill color for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param color            the color to be set in lv_color_t format
 */
void lv_vector_dsc_set_fill_color(lv_vector_dsc_t * dsc, lv_color_t color);

/**
 * Set fill opacity for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param opa              the opacity to be set in lv_opa_t format
 */
void lv_vector_dsc_set_fill_opa(lv_vector_dsc_t * dsc, lv_opa_t opa);

/**
 * Set fill rule for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param rule             the fill rule to be set in lv_vector_fill_t format
 */
void lv_vector_dsc_set_fill_rule(lv_vector_dsc_t * dsc, lv_vector_fill_t rule);

/**
 * Set the fill units for descriptor.
 * @param dsc              pointer to a vector graphic descriptor
 * @param units            the units to be set in lv_vector_fill_units_t format
 * @note The units can be either relative to the object bounding box or absolute in user space.
 *       This API specifically affects the drawing position of the fill image and does not impact other elements.
 */
void lv_vector_dsc_set_fill_units(lv_vector_dsc_t * dsc, const lv_vector_fill_units_t units);

/**
 * Set fill image for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param img_dsc          pointer to a `lv_draw_image_dsc_t` variable
 */
void lv_vector_dsc_set_fill_image(lv_vector_dsc_t * dsc, const lv_draw_image_dsc_t * img_dsc);

/**
 * Set fill linear gradient for descriptor
 * @param dsc pointer to a vector graphic descriptor
 * @param x1 the x for start point
 * @param y1 the y for start point
 * @param x2 the x for end point
 * @param y2 the y for end point
 */
void lv_vector_dsc_set_fill_linear_gradient(lv_vector_dsc_t * dsc, float x1, float y1, float x2, float y2);

/**

 * Set fill radial gradient radius for descriptor
 * @param dsc pointer to a vector graphic descriptor
 * @param cx the x for center of the circle
 * @param cy the y for center of the circle
 * @param radius the radius for circle
 */
void lv_vector_dsc_set_fill_radial_gradient(lv_vector_dsc_t * dsc, float cx, float cy, float radius);

/**
 * Set fill radial gradient spread for descriptor
 * @param dsc pointer to a vector graphic descriptor
 * @param spread the gradient spread to be set in lv_vector_gradient_spread_t format
 */
void lv_vector_dsc_set_fill_gradient_spread(lv_vector_dsc_t * dsc, lv_vector_gradient_spread_t spread);

/**
 * Set fill gradient color stops for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param stops            an array of `lv_grad_stop_t` variables
 * @param count            the number of stops in the array, range: 0..LV_GRADIENT_MAX_STOPS
 */
void lv_vector_dsc_set_fill_gradient_color_stops(lv_vector_dsc_t * dsc, const lv_grad_stop_t * stops,
                                                 uint16_t count);

/**
 * Set a matrix to current fill transformation matrix
 * @param dsc              pointer to a vector graphic descriptor
 * @param matrix           pointer to a matrix
 */
void lv_vector_dsc_set_fill_transform(lv_vector_dsc_t * dsc, const lv_matrix_t * matrix);

/**
 * Set stroke color for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param color            the color to be set in lv_color32_t format
 */
void lv_vector_dsc_set_stroke_color32(lv_vector_dsc_t * dsc, lv_color32_t color);

/**
 * Set stroke color for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param color            the color to be set in lv_color_t format
 */
void lv_vector_dsc_set_stroke_color(lv_vector_dsc_t * dsc, lv_color_t color);

/**
 * Set stroke opacity for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param opa              the opacity to be set in lv_opa_t format
 */
void lv_vector_dsc_set_stroke_opa(lv_vector_dsc_t * dsc, lv_opa_t opa);

/**
 * Set stroke line width for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param width            the stroke line width
 */
void lv_vector_dsc_set_stroke_width(lv_vector_dsc_t * dsc, float width);

/**
 * Set stroke line dash pattern for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param dash_pattern     an array of values that specify the segments of dash line
 * @param dash_count       the length of dash pattern array
 */
void lv_vector_dsc_set_stroke_dash(lv_vector_dsc_t * dsc, float * dash_pattern, uint16_t dash_count);

/**
 * Set stroke line cap style for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param cap              the line cap to be set in lv_vector_stroke_cap_t format
 */
void lv_vector_dsc_set_stroke_cap(lv_vector_dsc_t * dsc, lv_vector_stroke_cap_t cap);

/**
 * Set stroke line join style for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param join             the line join to be set in lv_vector_stroke_join_t format
 */
void lv_vector_dsc_set_stroke_join(lv_vector_dsc_t * dsc, lv_vector_stroke_join_t join);

/**
 * Set stroke miter limit for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param miter_limit      the stroke miter_limit
 */
void lv_vector_dsc_set_stroke_miter_limit(lv_vector_dsc_t * dsc, uint16_t miter_limit);

/**
 * Set stroke linear gradient for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param x1               the x for start point
 * @param y1               the y for start point
 * @param x2               the x for end point
 * @param y2               the y for end point
 */
void lv_vector_dsc_set_stroke_linear_gradient(lv_vector_dsc_t * dsc, float x1, float y1, float x2, float y2);
/**
 * Set stroke radial gradient for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param cx               the x for center of the circle
 * @param cy               the y for center of the circle
 * @param radius           the radius for circle
 */
void lv_vector_dsc_set_stroke_radial_gradient(lv_vector_dsc_t * dsc, float cx, float cy, float radius);

/**
 * Set stroke color stops for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
 */
void lv_vector_dsc_set_stroke_gradient_spread(lv_vector_dsc_t * dsc, lv_vector_gradient_spread_t spread);

/**
 * Set stroke color stops for descriptor
 * @param dsc              pointer to a vector graphic descriptor
 * @param stops            an array of `lv_grad_stop_t` variables
 * @param count            the number of stops in the array
 */
void lv_vector_dsc_set_stroke_gradient_color_stops(lv_vector_dsc_t * dsc, const lv_grad_stop_t * stops,
                                                   uint16_t count);

/**
 * Set a matrix to current stroke transformation matrix
 * @param dsc              pointer to a vector graphic descriptor
 * @param matrix           pointer to a matrix
 */
void lv_vector_dsc_set_stroke_transform(lv_vector_dsc_t * dsc, const lv_matrix_t * matrix);

/**
 * Set current transformation matrix to identity matrix
 * @param dsc           pointer to a vector graphic descriptor
 */
void lv_vector_dsc_identity(lv_vector_dsc_t * dsc);

/**
 * Change the scale factor of current transformation matrix
 * @param dsc           pointer to a vector graphic descriptor
 * @param scale_x       the scale factor for the X direction
 * @param scale_y       the scale factor for the Y direction
 */
void lv_vector_dsc_scale(lv_vector_dsc_t * dsc, float scale_x, float scale_y);

/**
 * Rotate current transformation matrix with origin
 * @param dsc           pointer to a vector graphic descriptor
 * @param degree        angle to rotate
 */
void lv_vector_dsc_rotate(lv_vector_dsc_t * dsc, float degree);

/**
 * Translate current transformation matrix to new position
 * @param dsc           pointer to a vector graphic descriptor
 * @param tx            the amount of translate in x direction
 * @param tx            the amount of translate in y direction
 */
void lv_vector_dsc_translate(lv_vector_dsc_t * dsc, float tx, float ty);

/**
 * Change the skew factor of current transformation matrix
 * @param dsc           pointer to a vector graphic descriptor
 * @param skew_x        the skew factor for x direction
 * @param skew_y        the skew factor for y direction
 */
void lv_vector_dsc_skew(lv_vector_dsc_t * dsc, float skew_x, float skew_y);

/**
 * Add a graphic path to the draw list
 * @param dsc           pointer to a vector graphic descriptor
 * @param path          pointer to a path
 */
void lv_vector_dsc_add_path(lv_vector_dsc_t * dsc, const lv_vector_path_t * path);

/**
 * Clear a rectangle area use current fill color
 * @param dsc           pointer to a vector graphic descriptor
 * @param rect          the area to clear in the buffer
 */
void lv_vector_clear_area(lv_vector_dsc_t * dsc, const lv_area_t * rect);

/**
 * Draw all the vector graphic paths
 * @param dsc           pointer to a vector graphic descriptor
 */
void lv_draw_vector(lv_vector_dsc_t * dsc);

/* Traverser for task list */
typedef void (*vector_draw_task_cb)(void * ctx, const lv_vector_path_t * path, const lv_vector_draw_dsc_t * dsc);

#endif /* LV_USE_VECTOR_GRAPHIC */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_DRAW_VECTOR_H */
