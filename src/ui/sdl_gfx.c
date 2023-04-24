#include "sdl_gfx.h"

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

void SDL_clear(SDL_Renderer* s) {
    SDL_SetRenderDrawColor(s, 0, 0, 0, 0xFF);
    SDL_RenderClear(s);
}

void SDL_pixel(SDL_Renderer* s, int x, int y, Color c) {
    SDL_SetRenderDrawColor(s, c -> r, c -> g, c -> b, c -> a);
    SDL_RenderDrawPoint(s, x, y);
}

void SDL_line(SDL_Renderer* s, int x1, int y1, int x2, int y2, Color c) {
    SDL_SetRenderDrawColor(s, c -> r, c -> g, c -> b, c -> a);
    SDL_RenderDrawLine(s, x1, y1, x2, y2);    
}

void SDL_3D_point(SDL_Renderer* s, Point3D p, Color c) {
    int x0 = SCREEN_WIDTH / 2;
    int y0 = SCREEN_HEIGHT / 2;
    Point2D p2 = p3d_project(p, x0, y0);
    SDL_pixel(s, (int) p2 -> x, (int) p2 -> y, c);
}

void SDL_3D_pixel(SDL_Renderer* s, int x, int y, int z, Color c) {
    SDL_3D_point(s, p3d_create(x, y, z), c);
}

void SDL_generate_cube(FaceSet fset, int x, int y, int z, int size, Color colors[]) {
    /*
    int sz = size * 0.5;
    Point3D a = p3d_create(x - sz, y - sz, z + sz);
    Point3D b = p3d_create(x + sz, y - sz, z + sz);
    Point3D c = p3d_create(x - sz, y + sz, z + sz);
    Point3D d = p3d_create(x + sz, y + sz, z + sz);
    
    Point3D e = p3d_create(x - sz, y - sz, z - sz);
    Point3D f = p3d_create(x + sz, y - sz, z - sz);
    Point3D g = p3d_create(x - sz, y + sz, z - sz);
    Point3D h = p3d_create(x + sz, y + sz, z - sz);
    
    faceset_addFace(fset, face_create(a, b, d, c, colors[0]));
    faceset_addFace(fset, face_create(a, c, g, e, colors[1]));
    faceset_addFace(fset, face_create(a, e, f, b, colors[2]));
    faceset_addFace(fset, face_create(b, f, h, d, colors[3]));
    faceset_addFace(fset, face_create(e, f, h, g, colors[4]));
    faceset_addFace(fset, face_create(g, c, d, h, colors[5]));*/

    /*
        // c(p1, p2, ...) := center of those points (center of the face)
        // c_total := c( c(p_a_1, p_a_2, ...), c(p_b_1, p_b_2, ...), ...) = center of all faces, center of the cube

        c(a, b, d, c) = (x, y, z + s)
        c(e, f, h, g) = (x, y, z - s)

        c(b, f, h, d) = (x + s, y, z)
        c(a, c, g, e) = (x - s, y, z)

        c(g, c, d, h) = (x, y + s, z)
        c(a, e, f, b) = (x, y - s, z)


        c_total = (x, y, z)
    */

    /*
        a (- - +)
        b (+ - +)
        c (- + +)
        d (+ + +)
        e (- - -)
        f (+ - -)
        g (- + -)
        h (+ + -)

        a b d c
        (- - +) (+ - +) (- + +) (+ + +) --> (* * +)
        a c g e 
        (- - +) (- + +) (- + -) (- - -) --> (- * *)
        a e f b
        (- - +) (- - -) (+ - -) (+ - +) --> (* - *)
        b f h d
        (+ - +) (+ - -) (+ + -) (+ + +) --> (+ * *)
        e f h g
        (- - -) (+ - -) (+ + -) (- + -) --> (* * -)
        g c d h
        (- + -) (- + +) (+ + +) (+ + -) --> (* + *)


    */

    int i, j;
    int f[6][4][3] = {
        { {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1} },
        { {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, -1} },
        { {-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}},
        { {1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
        { {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}},
        { {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}}
    };

    int sz = size * 0.5;
    for (i = 0; i < 6; i++) {
        Point3D p[4];
        for (j = 0; j < 4; j++) {
             int fx = f[i][j][0];
             int fy = f[i][j][1];
             int fz = f[i][j][2];
             p[j] = p3d_create(x + fx * sz, y + fy * sz, z + fz * sz);
             
        }
        Face face = face_create(p[0], p[1], p[2], p[3], colors[i]);
        faceset_addFace(fset, face);
        //face_print(face);
    }
}

void SDL_fill_face(SDL_Renderer* s, Face face, Light l) {
    Color facecolor = light_color(l, face -> center, color_multiply(face -> color, 0.5), 0.5);
    SDL_SetRenderDrawColor(s, facecolor -> r, facecolor -> g, facecolor -> b, facecolor -> a);
    int x0 = SCREEN_WIDTH / 2;
    int y0 = SCREEN_HEIGHT / 2;    
    Point2D corners[4];
    corners[0] = p3d_project((face -> a), x0, y0);
    corners[1] = p3d_project((face -> b), x0, y0);
    corners[2] = p3d_project((face -> c), x0, y0);
    corners[3] = p3d_project((face -> d), x0, y0);
    int minY = min(min(min(corners[0] -> y, corners[1] -> y), corners[2] -> y), corners[3] -> y);
    int maxY = max(max(max(corners[0] -> y, corners[1] -> y), corners[2] -> y), corners[3] -> y);
    
    double y;
    for (y = minY - 1; y < maxY + 1; y ++) { 

        int n = 0;
        double nodes[4];
        int i;
        int t = 3;
        for (i = 0; i < 4; i++) {
            if ( (corners[i] -> y < y && corners[t] -> y >= y) || (corners[t] -> y < y && corners[i] -> y >= y) ) {
                nodes[n++] = corners[i] -> x + (y - corners[i] -> y) / (corners[t] -> y - corners[i] -> y) * (corners[t] -> x - corners[i] -> x);
            }
            t = i;
        }
        
        i = 0;
        while (i < n - 1) {
            if (nodes[i] > nodes[i + 1]) {
                int swap = nodes[i];
                nodes[i] = nodes[i + 1];
                nodes[i + 1] = swap;
                if (i) i--;
            } else {
                i++;
            }
        }
 
        for (i = 0; i < n; i += 2) {
            SDL_RenderDrawLine(s, nodes[i] - 1, y, nodes[i + 1] + 1, y);
        }
    }

    int i;
    for (i = 0; i < 4; i++) {
        p2d_destroy(corners[i]);
    }
}

void SDL_draw_surface(SDL_Renderer* s, FaceSet fset, Light l) {
    int i;
    for (i = 0; i < fset -> size; i++) {
        Face face = fset -> array[i];
        SDL_fill_face(s, face, l);
    } 
}

void show_axis(SDL_Renderer* s, int size) {
    Color c = color_create(255, 0, 0, 255);
    int i;
    for (i = 0; i < size; i++) {
        SDL_3D_pixel(s, i, 0, 0, c); 
        SDL_3D_pixel(s, 0, i, 0, c); 
        SDL_3D_pixel(s, 0, 0, i, c); 
    }
    color_destroy(c);
}