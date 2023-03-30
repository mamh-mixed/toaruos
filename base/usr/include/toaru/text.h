#pragma once
/**
 * @file toaru/text.h
 * @brief TrueType glyph rasterizer.
 *
 * Exposed API for the TrueType renderer.
 */
#include <stdint.h>

/* Methods for loading fonts */
extern struct TT_Font * tt_font_from_file(const char * fileName);
extern struct TT_Font * tt_font_from_shm(const char * identifier);

/* Methods for changing font sizes */
extern void tt_set_size(struct TT_Font * font, float sizeInEm);
extern void tt_set_size_px(struct TT_Font * font, float sizeInPx);

/* Methods for dealing with glyphs */
extern void tt_draw_glyph(gfx_context_t * ctx, struct TT_Font * font, int x_offset, int y_offset, unsigned int glyph, uint32_t color);
extern int tt_glyph_for_codepoint(struct TT_Font * font, unsigned int codepoint);
extern int tt_xadvance_for_glyph(struct TT_Font * font, unsigned int ind);
extern float tt_glyph_width(struct TT_Font * font, unsigned int glyph);
extern sprite_t * tt_bake_glyph(struct TT_Font * font, unsigned int glyph, uint32_t color, int *_x, int *_y, float xadjust);

/* Convenience functions for dealing with whole strings */
extern int tt_string_width(struct TT_Font * font, const char * s);
extern int tt_string_width_int(struct TT_Font * font, const char * s);
extern int tt_draw_string(gfx_context_t * ctx, struct TT_Font * font, int x, int y, const char * s, uint32_t color);
extern void tt_draw_string_shadow(gfx_context_t * ctx, struct TT_Font * font, char * string, int font_size, int left, int top, uint32_t text_color, uint32_t shadow_color, int blur);

struct TT_FontMetrics {
	float ascender;
	float descender;
	float lineGap;
};

extern int tt_measure_font(struct TT_Font * font, struct TT_FontMetrics * metrics);

/* Vector rasterizer engine */
extern struct TT_Contour * tt_contour_start(float x, float y);
extern struct TT_Shape * tt_contour_finish(struct TT_Contour * in);
extern struct TT_Shape * tt_contour_stroke_shape(struct TT_Contour * in, float width);
extern struct TT_Contour * tt_contour_line_to(struct TT_Contour * shape, float x, float y);
extern struct TT_Contour * tt_contour_move_to(struct TT_Contour * shape, float x, float y);
extern void tt_path_paint(gfx_context_t * ctx, const struct TT_Shape * shape, uint32_t color);
extern void tt_contour_transform(struct TT_Contour * cnt, gfx_matrix_t matrix);

/* Internal methods to draw paths into vector contours */
extern struct TT_Contour * tt_draw_glyph_into(struct TT_Contour * contour, struct TT_Font * font, float x_offset, float y_offset, unsigned int glyph);
extern struct TT_Contour * tt_prepare_string(struct TT_Font * font, float x, float y, const char * s, float * out_width);
