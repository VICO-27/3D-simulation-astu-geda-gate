#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

// --- CONSTANTS ---
const double PI = 3.14159265358979323846;
const double ARCH_THICKNESS = 0.35;    
const float  GATE_DEPTH     = 1.5f;    
const float  WALL_EPS       = 0.02f;   

// SCREEN
const int WINDOW_W = 1000;
const int WINDOW_H = 600;

// CAMERA GLOBALS
float camX = 0.0f;
float camY = 40.0f; 
float camZ = 140.0f; 

// --- COLORS ---
struct Color { float r, g, b; };
const Color COL_SKY      = { 0.53f, 0.81f, 0.98f }; 
const Color COL_GROUND   = { 0.13f, 0.40f, 0.13f }; 
const Color COL_CITY_GND = { 0.35f, 0.35f, 0.38f }; 
const Color COL_CITY_BLD = { 0.70f, 0.70f, 0.75f }; 
const Color COL_WALL     = { 0.92f, 0.82f, 0.72f }; 
const Color COL_ARCH     = { 0.70f, 0.70f, 0.75f }; 
const Color COL_ARCH_OUT = { 0.45f, 0.45f, 0.50f }; 
const Color COL_RUNG     = { 0.88f, 0.78f, 0.68f }; 
const Color COL_ROAD     = { 0.20f, 0.20f, 0.20f }; 
const Color COL_PAVEMENT = { 0.40f, 0.40f, 0.42f }; 
const Color COL_WALKWAY  = { 0.60f, 0.60f, 0.65f }; 
const Color COL_PARKING  = { 0.30f, 0.30f, 0.32f }; 
const Color COL_SOIL     = { 0.45f, 0.35f, 0.25f }; 
const Color COL_COBBLE   = { 0.55f, 0.55f, 0.58f }; 
const Color COL_PARKING_LINE = { 1.0f, 0.85f, 0.0f }; 

// House Colors
const Color COL_ROOF     = { 0.60f, 0.20f, 0.10f };
const Color COL_ROOF_2   = { 0.30f, 0.30f, 0.35f };
const Color COL_HOUSE_W  = { 0.90f, 0.88f, 0.85f };
const Color COL_HOUSE_W2 = { 0.80f, 0.75f, 0.70f };

// Fence Colors
const Color COL_FENCE_STONE  = { 0.55f, 0.50f, 0.45f }; 
const Color COL_FENCE_CONC   = { 0.65f, 0.65f, 0.67f }; 
const Color COL_FENCE_STRIPE = { 0.95f, 0.95f, 0.95f }; 
const Color COL_FENCE_PILLAR = { 0.50f, 0.05f, 0.05f }; 
const Color COL_FENCE_METAL  = { 0.10f, 0.10f, 0.10f }; 
const Color COL_PLANTER_SOIL = { 0.35f, 0.25f, 0.15f }; 

// Props
const Color COL_BENCH_WOOD = { 0.60f, 0.40f, 0.20f };
const Color COL_BUS_BODY   = { 0.95f, 0.85f, 0.10f }; 
const Color COL_BUS_WIN    = { 0.20f, 0.20f, 0.80f };
const Color COL_TRUNK    = { 0.45f, 0.30f, 0.15f }; 
const Color COL_LEAVES   = { 0.05f, 0.55f, 0.05f };
const Color COL_PENCIL   = { 0.02f, 0.40f, 0.02f }; 
const Color COL_IRON     = { 0.10f, 0.10f, 0.10f }; 
const Color COL_PAINT    = { 0.95f, 0.95f, 0.95f }; 

// Skin & Shirt Colors
const Color COL_SKIN     = { 0.96f, 0.80f, 0.69f };
const Color COL_SHIRT1   = { 0.8f, 0.2f, 0.2f };
const Color COL_SHIRT2   = { 0.2f, 0.2f, 0.8f };
const Color COL_SHIRT3   = { 0.9f, 0.9f, 0.9f };
const Color COL_PANTS    = { 0.1f, 0.1f, 0.1f };

// Building Colors
const Color COL_BLD_BLUE   = { 0.75f, 0.80f, 0.90f }; 
const Color COL_BLD_BRICK  = { 0.70f, 0.35f, 0.30f }; 
const Color COL_BLD_BEIGE  = { 0.85f, 0.80f, 0.70f }; 
const Color COL_BLD_GREY   = { 0.50f, 0.50f, 0.55f }; 
const Color COL_BLD_TRIM   = { 0.40f, 0.40f, 0.45f }; 
const Color COL_WINDOW     = { 0.20f, 0.30f, 0.50f }; 

// Logo Colors
const Color LOGO_RED   = { 0.75f, 0.0f, 0.0f }; 
const Color LOGO_GREEN = { 0.18f, 0.49f, 0.20f }; 
const Color LOGO_BLUE  = { 0.25f, 0.32f, 0.71f }; 
const Color LOGO_WHITE = { 1.0f, 1.0f, 1.0f };
const Color LOGO_BROWN = { 0.43f, 0.30f, 0.25f }; 

// --- CAR COLORS ---
const Color FL_ARG_BLU = { 0.40f, 0.70f, 0.98f }; 
const Color FL_SID_RED = { 0.90f, 0.10f, 0.10f }; 
const Color FL_SID_GRN = { 0.05f, 0.75f, 0.15f }; 
const Color FL_TAXI_YEL= { 1.0f, 0.8f, 0.0f };

// --- ETHIOPIAN FLAG COLORS ---
const Color COL_ETH_GREEN  = { 0.00f, 0.58f, 0.22f };
const Color COL_ETH_YELLOW = { 0.98f, 0.85f, 0.08f };
const Color COL_ETH_RED    = { 0.85f, 0.09f, 0.12f };
const Color COL_ETH_BLUE   = { 0.05f, 0.28f, 0.63f };

// --- LAYERING HEIGHTS ---
const float Y_GROUND = 0.00f;
const float Y_COBBLE = 0.015f;
const float Y_ROAD   = 0.030f;
const float Y_PAINT  = 0.040f;

 
const Color COL_CLOUD = { 1.0f, 1.0f, 1.0f };      // Pure White
const Color COL_BIRD  = { 0.05f, 0.05f, 0.05f };   // Black/Dark Grey
const Color COL_EAGLE = { 0.35f, 0.25f, 0.15f };   // Dark Brown



// --- MATH HELPERS ---
float getCircleY(float x, float cx, float r) {
    float val = r*r - (x - cx)*(x - cx);
    if (val < 0) return 0.0f;
    return sqrt(val);
}
float solveIntersection(float c1, float r1, float c2, float r2) {
    float numerator = (r2*r2) - (r1*r1) + (c1*c1) - (c2*c2);
    float denominator = 2.0f * (c1 - c2);
    if (std::abs(denominator) < 0.0001) return 0.0f; 
    return numerator / denominator;
}

// --- 3D UTILS ---
void setMaterial(Color c) {
    glColor3f(c.r, c.g, c.b);
    GLfloat mat[] = { c.r, c.g, c.b, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat);
    GLfloat no_emit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_emit);
}

void drawBox(float w, float h, float d) {
    glPushMatrix(); glScalef(w, h, d); glutSolidCube(1.0f); glPopMatrix();
}

void drawSolidCircle2D(float r, Color col) {
    glColor3f(col.r, col.g, col.b);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(0,0);
    for(int i = 0; i <= 60; i++) { float t = 2.0f*PI*i/60; glVertex2f(r*cos(t), r*sin(t)); }
    glEnd();
}

// --- LOGO GEOMETRY ---
void drawDetailedLogoGeometry(float r) {
    drawSolidCircle2D(r, LOGO_RED);
    glColor3f(1,1,1); glLineWidth(2.0f); glBegin(GL_LINES);
    for(float a=0.5; a<2.6; a+=0.1) { glVertex2f(r*0.9*cos(a), r*0.9*sin(a)); glVertex2f((r*0.9-0.03)*cos(a), (r*0.9-0.03)*sin(a)); }
    for(float a=3.6; a<5.8; a+=0.06) { glVertex2f(r*0.9*cos(a), r*0.9*sin(a)); glVertex2f((r*0.9-0.03)*cos(a), (r*0.9-0.03)*sin(a)); }
    glEnd();
    drawSolidCircle2D(r * 0.80f, LOGO_WHITE);
    float ir = r * 0.75f; 
    glColor3f(LOGO_GREEN.r, LOGO_GREEN.g, LOGO_GREEN.b); glBegin(GL_TRIANGLE_FAN); glVertex2f(0, 0); 
    for(int i=0; i<=180; i++) { float angle = i * (PI / 180.0f); float gearR = ir * (0.95f + 0.05f * sin(angle * 10.0f)); glVertex2f(gearR * cos(angle), gearR * sin(angle)); } glEnd();
    drawSolidCircle2D(ir*0.08f, LOGO_WHITE); 
    glColor3f(LOGO_BLUE.r, LOGO_BLUE.g, LOGO_BLUE.b); glBegin(GL_TRIANGLE_FAN); glVertex2f(0, 0); for(int i=180; i<=360; i++) { float angle = i * (PI / 180.0f); glVertex2f(ir * 0.95f * cos(angle), ir * 0.95f * sin(angle)); } glEnd();
}

void drawASTULogoGeometry(float r) {
    drawSolidCircle2D(r, LOGO_RED);
    drawSolidCircle2D(r * 0.8f, LOGO_WHITE);
    float innerR = r * 0.8f;
    glColor3f(LOGO_BLUE.r, LOGO_BLUE.g, LOGO_BLUE.b);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(0,0);
    for(int i=180; i<=360; i++) {
        float rad = i * PI / 180.0f;
        glVertex2f(innerR * cos(rad), innerR * sin(rad));
    }
    glEnd();
    glColor3f(1,1,1); glLineWidth(1.0f); glBegin(GL_LINES);
    for(float x = -0.6; x <= 0.6; x+=0.3) {
        glVertex2f(innerR * x, 0); glVertex2f(innerR * x * 0.2, -innerR);
    }
    glVertex2f(-innerR, 0); glVertex2f(innerR, 0);
    glVertex2f(-innerR*0.8, -innerR*0.4); glVertex2f(innerR*0.8, -innerR*0.4);
    glEnd();
    glColor3f(LOGO_GREEN.r, LOGO_GREEN.g, LOGO_GREEN.b);
    glBegin(GL_TRIANGLE_FAN); glVertex2f(0, 0);
    for(int i=0; i<=180; i++) {
        float rad = i * PI / 180.0f;
        float gear = innerR * 0.7f + (innerR * 0.05f * sin(rad * 20.0f)); 
        glVertex2f(gear * cos(rad), gear * sin(rad));
    }
    glEnd();
    glColor3f(1,1,1); 
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(-0.3f*r, 0.1f*r); glVertex2f(-0.3f*r, -0.2f*r); glVertex2f(0, -0.1f*r);
    glVertex2f(0, 0); glVertex2f(0.3f*r, 0.1f*r); glVertex2f(0.3f*r, -0.2f*r); glVertex2f(0, -0.1f*r);
    glEnd();
    glColor3f(LOGO_BROWN.r, LOGO_BROWN.g, LOGO_BROWN.b); glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0); glVertex2f(-0.3f*r, 0.1f*r); glVertex2f(-0.3f*r, -0.2f*r); glVertex2f(0, -0.1f*r);
    glVertex2f(0.3f*r, -0.2f*r); glVertex2f(0.3f*r, 0.1f*r);
    glEnd();
    glColor3f(1,1,1); glLineWidth(1.5f);
    for(int k=0; k<3; k++) {
        glPushMatrix();
        glTranslatef(0, 0.4f*r, 0);
        glRotatef(k * 60, 0, 0, 1);
        glScalef(1.0f, 0.3f, 1.0f);
        glBegin(GL_LINE_LOOP);
        for(int j=0; j<30; j++) {
            float th = j * 2.0f * PI / 30.0f;
            glVertex2f(0.25f*r * cos(th), 0.25f*r * sin(th));
        }
        glEnd();
        glPopMatrix();
    }
    glColor3f(1,1,1);
    float textR = r * 0.9f;
    glBegin(GL_POINTS); 
    for(int i=200; i<=340; i+=4) {
        float rad = i * PI / 180.0f;
        glVertex2f(textR * cos(rad), textR * sin(rad));
    }
    glEnd();
}

// --- STANDARD OBJECTS ---
void drawBus(float x, float z, float angle) {
    glPushMatrix(); glTranslatef(x, 0.75f, z); glRotatef(angle, 0, 1, 0);
    setMaterial(COL_BUS_BODY); drawBox(1.8f, 1.5f, 4.5f); setMaterial(COL_BUS_WIN); glPushMatrix(); glTranslatef(0.91f, 0.3f, 0); drawBox(0.1f, 0.6f, 3.8f); glPopMatrix(); glPushMatrix(); glTranslatef(-0.91f, 0.3f, 0); drawBox(0.1f, 0.6f, 3.8f); glPopMatrix(); glPushMatrix(); glTranslatef(0, 0.3f, 2.2f); drawBox(1.6f, 0.6f, 0.1f); glPopMatrix(); setMaterial(COL_IRON); glPushMatrix(); glTranslatef(0.9f, -0.7f, 1.2f); drawBox(0.3f, 0.6f, 0.6f); glPopMatrix(); glPushMatrix(); glTranslatef(-0.9f, -0.7f, 1.2f); drawBox(0.3f, 0.6f, 0.6f); glPopMatrix(); glPushMatrix(); glTranslatef(0.9f, -0.7f, -1.2f); drawBox(0.3f, 0.6f, 0.6f); glPopMatrix(); glPushMatrix(); glTranslatef(-0.9f, -0.7f, -1.2f); drawBox(0.3f, 0.6f, 0.6f); glPopMatrix(); glPopMatrix();
}

void drawBench(float x, float z, float angle) {
    glPushMatrix(); glTranslatef(x, 0.2f, z); glRotatef(angle, 0, 1, 0);
    setMaterial(COL_BENCH_WOOD); drawBox(1.2f, 0.1f, 0.4f); glPushMatrix(); glTranslatef(0, 0.25f, -0.2f); glRotatef(-10, 1, 0, 0); drawBox(1.2f, 0.4f, 0.05f); glPopMatrix(); setMaterial(COL_IRON); glPushMatrix(); glTranslatef(0.5f, -0.2f, 0); drawBox(0.1f, 0.4f, 0.3f); glPopMatrix(); glPushMatrix(); glTranslatef(-0.5f, -0.2f, 0); drawBox(0.1f, 0.4f, 0.3f); glPopMatrix(); glPopMatrix();
}

void drawTable(float x, float z) {
    glPushMatrix(); glTranslatef(x, 0, z);
    setMaterial(COL_BENCH_WOOD);
    glPushMatrix(); glTranslatef(-0.4f, 0.3f, -0.4f); drawBox(0.1f, 0.6f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.4f, 0.3f, -0.4f); drawBox(0.1f, 0.6f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.4f, 0.3f, 0.4f); drawBox(0.1f, 0.6f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.4f, 0.3f, 0.4f); drawBox(0.1f, 0.6f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0.6f, 0); drawBox(1.2f, 0.05f, 1.2f); glPopMatrix();
    drawBench(0, -0.8f, 0); drawBench(0, 0.8f, 180);
    glPopMatrix();
}

void drawCircularSeat(float x, float z) {
    glPushMatrix(); glTranslatef(x, 0.2f, z); glRotatef(-90, 1, 0, 0); 
    setMaterial(COL_WALKWAY); glutSolidTorus(0.2, 1.5, 10, 30); 
    glRotatef(90, 1, 0, 0); setMaterial(COL_LEAVES); glPushMatrix(); glTranslatef(0, 0.2f, 0); glutSolidSphere(0.8, 8, 8); glPopMatrix(); glPopMatrix();
}

void drawShrub(float x, float z) {
    glPushMatrix(); glTranslatef(x, 0.3f, z);
    setMaterial(COL_LEAVES); 
    glutSolidSphere(0.4f, 6, 6);
    glTranslatef(0.3f, -0.1f, 0.2f); glutSolidSphere(0.3f, 6, 6);
    glTranslatef(-0.6f, 0.0f, -0.1f); glutSolidSphere(0.35f, 6, 6);
    glPopMatrix();
}

void drawPlanterWithShrubs(float x, float z, float w, float l, int numShrubs) {
    glPushMatrix(); glTranslatef(x, 0.02f, z); 
    setMaterial(COL_PLANTER_SOIL);
    float soilH = 0.05f; 
    glPushMatrix(); glTranslatef(0, 0, 0); glScalef(w, soilH, l - w); glutSolidCube(1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0, (l - w) / 2.0f); glScalef(w * 0.5f, soilH, w * 0.5f); glutSolidSphere(1.0, 12, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0, -(l - w) / 2.0f); glScalef(w * 0.5f, soilH, w * 0.5f); glutSolidSphere(1.0, 12, 12); glPopMatrix();
    if (numShrubs > 0) {
        float step = (l - 1.0f) / (float)numShrubs; 
        float startZ = - (l / 2.0f) + (step / 2.0f) + 0.5f;
        for (int i = 0; i < numShrubs; i++) { float pz = startZ + i * step; drawShrub(0, pz); }
    }
    glPopMatrix();
}

void drawBuildingByFloors(float x, float z, int floors, float width, float depth, Color tint) {
    float floorHeight = 2.8f; float totalHeight = floors * floorHeight;
    glPushMatrix(); glTranslatef(x, totalHeight/2.0f, z);
    setMaterial(tint); drawBox(width, totalHeight, depth); setMaterial(COL_WINDOW); float wGap = 1.8f; float zFace = depth/2.0f + 0.05f; 
    for (int f = 0; f < floors; f++) { float yPos = -totalHeight/2.0f + 1.2f + (f * floorHeight); for(float dx = -width/2.0f + 1.2f; dx < width/2.0f - 1.0f; dx += wGap) { glPushMatrix(); glTranslatef(dx, yPos, zFace); drawBox(1.0f, 1.2f, 0.1f); glPopMatrix(); } }
    setMaterial(COL_BLD_TRIM); glPushMatrix(); glTranslatef(0, totalHeight/2.0f + 0.1f, 0); drawBox(width+0.5f, 0.2f, depth+0.5f); glPopMatrix(); glPopMatrix();
}

void drawBuildingWithWalkway(float x, float z, int floors, float width, float depth, Color tint) {
    glPushMatrix(); glTranslatef(x, 0.02f, z); setMaterial(COL_WALKWAY); glScalef(width + 6.0f, 0.05f, depth + 6.0f); glutSolidCube(1.0f); glPopMatrix();
    drawBuildingByFloors(x, z, floors, width, depth, tint);
}

void drawVariedHouse(float x, float z, float angle, int type) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(angle, 0, 1, 0);
    
    // Type 0: Standard Gable Roof
    if (type % 4 == 0) {
        setMaterial(COL_HOUSE_W);
        glPushMatrix(); glTranslatef(0, 2.0f, 0); drawBox(6.0f, 4.0f, 6.0f); glPopMatrix();
        setMaterial(COL_ROOF);
        glPushMatrix(); glTranslatef(0, 4.0f, 0); glScalef(6.5f, 2.5f, 6.5f); glRotatef(-45, 0, 1, 0); glutSolidCone(0.75, 1.0, 4, 1); glPopMatrix();
    }
    // Type 1: Flat Roof Modern
    else if (type % 4 == 1) {
        setMaterial(COL_BLD_BEIGE);
        glPushMatrix(); glTranslatef(0, 2.5f, 0); drawBox(7.0f, 5.0f, 6.0f); glPopMatrix();
        setMaterial(COL_CITY_BLD);
        glPushMatrix(); glTranslatef(0, 5.1f, 0); drawBox(7.2f, 0.2f, 6.2f); glPopMatrix();
    }
    // Type 2: Small Apartment (Taller)
    else if (type % 4 == 2) {
        setMaterial(COL_HOUSE_W2);
        glPushMatrix(); glTranslatef(0, 4.0f, 0); drawBox(5.0f, 8.0f, 5.0f); glPopMatrix();
        setMaterial(COL_ROOF_2);
        glPushMatrix(); glTranslatef(0, 8.0f, 0); glScalef(5.2f, 1.0f, 5.2f); glutSolidCube(1.0f); glPopMatrix();
    }
    // Type 3: Villa with Porch
    else {
        setMaterial(COL_WALL);
        glPushMatrix(); glTranslatef(0, 2.0f, 0); drawBox(8.0f, 4.0f, 5.0f); glPopMatrix();
        setMaterial(COL_ROOF);
        glPushMatrix(); glTranslatef(0, 4.0f, 0); glScalef(8.5f, 2.0f, 5.5f); glRotatef(90, 0, 1, 0); glutSolidCylinder(0.5, 1.0, 3, 1); glPopMatrix(); 
    }
    glPopMatrix();
}

void drawLEDScreen() {
    float x = 28.0f; float z = 4.0f;
    glPushMatrix(); glTranslatef(x, 0, z);
    // Pole
    setMaterial(COL_IRON); glPushMatrix(); glTranslatef(0, 2.0f, 0); drawBox(0.5f, 4.0f, 0.5f); glPopMatrix();
    // Frame
    setMaterial(COL_IRON); glPushMatrix(); glTranslatef(0, 5.5f, 0); drawBox(6.0f, 3.5f, 0.5f); glPopMatrix();
    // Screen Back
    glColor3f(0,0,0); glPushMatrix(); glTranslatef(0, 5.5f, 0.26f); drawBox(5.6f, 3.1f, 0.05f); glPopMatrix();
    
    // Text Logic
    int t = glutGet(GLUT_ELAPSED_TIME); 
    int stage = (t / 1000) % 4; // Change color every second
    Color textColor;
    if (stage == 0) textColor = LOGO_RED;
    else if (stage == 1) textColor = LOGO_GREEN;
    else if (stage == 2) textColor = LOGO_WHITE;
    else textColor = COL_ETH_YELLOW; // Yellow

    glColor3f(textColor.r, textColor.g, textColor.b); 
    glLineWidth(4.0f); // Bold
    glPushMatrix(); 
    glTranslatef(-2.6f, 5.15f, 0.40f); 
    glScalef(0.013f, 0.013f, 1.0f); 
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A'); 
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S'); 
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T'); 
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'U'); 
    glPopMatrix(); 
    glLineWidth(1.0f); // Reset
    glPopMatrix();
}

void drawStreetLight(float x, float z, float angle) {
    glPushMatrix(); glTranslatef(x, 0, z); glRotatef(angle, 0, 1, 0);
    setMaterial(COL_IRON); glPushMatrix(); glTranslatef(0, 3.0f, 0); drawBox(0.2f, 6.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 5.8f, 0.4f); drawBox(0.15f, 0.15f, 1.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 5.7f, 0.8f); GLfloat emission[] = { 1.0f, 1.0f, 0.8f, 1.0f }; glMaterialfv(GL_FRONT, GL_EMISSION, emission); glColor3f(1.0f, 1.0f, 0.8f); glutSolidSphere(0.25f, 8, 8);
    GLfloat no_emit[] = { 0.0f, 0.0f, 0.0f, 1.0f }; glMaterialfv(GL_FRONT, GL_EMISSION, no_emit); glPopMatrix(); glPopMatrix();
}

void drawPencilTree(float x, float z) {
    glPushMatrix(); glTranslatef(x, 0, z); setMaterial(COL_TRUNK);
    glPushMatrix(); glRotatef(-90, 1, 0, 0); GLUquadric* q = gluNewQuadric(); gluCylinder(q, 0.08, 0.08, 1.0, 6, 1); gluDeleteQuadric(q); glPopMatrix();
    setMaterial(COL_PENCIL); glPushMatrix(); glTranslatef(0, 1.0f, 0); glRotatef(-90, 1, 0, 0); q = gluNewQuadric(); gluCylinder(q, 0.3, 0.0, 3.5, 8, 1); gluDeleteQuadric(q); glPopMatrix(); glPopMatrix();
}

void drawVariedPlant(float x, float z, int seed) {
    glPushMatrix(); glTranslatef(x, 0, z);
    int type = seed % 3;
    if (type == 0) { glScalef(1.8f, 2.8f, 1.8f); } else if (type == 1) { glScalef(2.5f, 2.0f, 2.5f); } else { glScalef(2.2f, 2.2f, 2.2f); }
    drawShrub(0, 0); glPopMatrix();
}

// --- ANIMATION HELPERS ---
// Added "flat" parameter to stop waving for ASTU flag
float getWaveZ(float x, float phase, bool isSolid, bool flat) { 
    if (isSolid || flat) return 0.0f; 
    return sin(x * 1.5f + phase * 2.0f) * (0.2f + x * 0.1f);
}
void drawWavedVertex(float x, float y, float zBase, float phase, bool isSolid, bool flat) { float zOff = getWaveZ(x, phase, isSolid, flat); glVertex3f(x, y, zBase + zOff); }
void drawWavedStripe(float x, float y, float w, float h, float phase, Color c, bool isSolid, bool flat) { glColor3f(c.r, c.g, c.b); int segs = 10; glBegin(GL_QUAD_STRIP); for(int i=0; i<=segs; i++) { float fx = x + (w * i / (float)segs); drawWavedVertex(fx, y, 0, phase, isSolid, flat); drawWavedVertex(fx, y + h, 0, phase, isSolid, flat); } glEnd(); }
void drawWavedTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float phase, Color c, bool isSolid) { glColor3f(c.r, c.g, c.b); glBegin(GL_TRIANGLES); drawWavedVertex(x1, y1, 0, phase, isSolid, false); drawWavedVertex(x2, y2, 0, phase, isSolid, false); drawWavedVertex(x3, y3, 0, phase, isSolid, false); glEnd(); }
void drawWavedCircle(float cx, float cy, float r, float phase, Color c, bool isSolid) { glColor3f(c.r, c.g, c.b); glBegin(GL_TRIANGLE_FAN); drawWavedVertex(cx, cy, 0.01f, phase, isSolid, false); for(int i=0; i<=20; i++) { float ang = i * 2.0f * PI / 20.0f; float px = cx + r * cos(ang); float py = cy + r * sin(ang); drawWavedVertex(px, py, 0.01f, phase, isSolid, false); } glEnd(); }

void drawWavedPentagram(float cx, float cy, float r, float phase, Color c) {
    glColor3f(c.r, c.g, c.b); float innerR = r * 0.382f; 
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 5; i++) {
        float angle1 = (90.0f + i * 72.0f) * PI / 180.0f; 
        float angle2 = (90.0f + 36.0f + i * 72.0f) * PI / 180.0f;
        float angle3 = (90.0f - 36.0f + i * 72.0f) * PI / 180.0f;
        float p1x = cx + r * cos(angle1);     float p1y = cy + r * sin(angle1);
        float p2x = cx + innerR * cos(angle2); float p2y = cy + innerR * sin(angle2);
        float p3x = cx + innerR * cos(angle3); float p3y = cy + innerR * sin(angle3);
        drawWavedVertex(cx, cy, 0.02f, phase, false, false); drawWavedVertex(p3x, p3y, 0.02f, phase, false, false); drawWavedVertex(p2x, p2y, 0.02f, phase, false, false);
        drawWavedVertex(p1x, p1y, 0.02f, phase, false, false); drawWavedVertex(p3x, p3y, 0.02f, phase, false, false); drawWavedVertex(p2x, p2y, 0.02f, phase, false, false);
    }
    glEnd();
}

float getAnimTime() { return glutGet(GLUT_ELAPSED_TIME) * 0.005f; }

void drawFlag(float xPos, float zPos, float height, int type) {
    float poleH=6.5f, fW=3.5f, fH=2.0f;
    setMaterial(COL_IRON); glPushMatrix(); glTranslatef(xPos,0,zPos); glRotatef(-90,1,0,0); GLUquadric* q=gluNewQuadric(); gluCylinder(q,0.1,0.1,poleH,8,1); gluSphere(q,0.15,8,8); gluDeleteQuadric(q); glPopMatrix();
    float time = getAnimTime();
    glPushMatrix(); glTranslatef(xPos, height, zPos); glDisable(GL_LIGHTING); 
    
    if (type == 0) { // ETHIOPIA (Waving)
        drawWavedStripe(0, 0, fW, -fH/3.0f, time, COL_ETH_GREEN, false, false);
        drawWavedStripe(0, -fH/3.0f, fW, -fH/3.0f, time, COL_ETH_YELLOW, false, false);
        drawWavedStripe(0, -2.0f*fH/3.0f, fW, -fH/3.0f, time, COL_ETH_RED, false, false);
        float cx = fW / 2.0f; float cy = -fH / 2.0f; float emblemR = fH * 0.25f; 
        glPushMatrix(); glTranslatef(0, 0, 0.02f); drawWavedCircle(cx, cy, emblemR, time, COL_ETH_BLUE, false);
        glTranslatef(0, 0, 0.01f); drawWavedPentagram(cx, cy, emblemR * 0.9f, time, COL_ETH_YELLOW);
        glPopMatrix();
    } else { // ASTU LOGO (Static/Flat as requested)
        drawWavedStripe(0, 0, fW, -fH, time, LOGO_WHITE, false, true); 
        float cx = fW / 2.0f; float cy = -fH / 2.0f;
        glPushMatrix(); 
        glTranslatef(cx, cy, 0.05f); 
        glScalef(0.4f, 0.4f, 1.0f); 
        drawASTULogoGeometry(2.0f); 
        glPopMatrix();
    }
    glEnable(GL_LIGHTING); glPopMatrix();
}

// --- LANDSCAPE UTILS ---
void drawTree(float x, float z) { 
    glPushMatrix(); glTranslatef(x, 0, z); 
    if (z > 1.0f) { glDisable(GL_LIGHTING); glColor3f(COL_GROUND.r, COL_GROUND.g, COL_GROUND.b); glPushMatrix(); glTranslatef(0, 0.03f, 0); glRotatef(-90, 1, 0, 0); drawSolidCircle2D(1.8f, COL_GROUND); glPopMatrix(); glEnable(GL_LIGHTING); }
    setMaterial(COL_TRUNK); glPushMatrix(); glRotatef(-90, 1, 0, 0); GLUquadric* q = gluNewQuadric(); gluCylinder(q, 0.1, 0.1, 0.7, 8, 1); gluDeleteQuadric(q); glPopMatrix(); 
    setMaterial(COL_LEAVES); glPushMatrix(); glTranslatef(0, 0.6f, 0); glRotatef(-90, 1, 0, 0); q = gluNewQuadric(); gluCylinder(q, 0.45, 0.0, 1.4, 10, 1); gluDeleteQuadric(q); glPopMatrix(); 
    glPopMatrix(); 
}







void drawCeramicPatch(float x, float z, float w, float l) {
    float tileSize = 2.0f;
    for(float i = 0; i < w; i += tileSize) {
        for(float j = 0; j < l; j += tileSize) {
            setMaterial(COL_HOUSE_W); // Beige Ceramic color
            glBegin(GL_QUADS); glNormal3f(0, 1, 0);
            glVertex3f(x + i, 0.011f, z - j); glVertex3f(x + i + tileSize, 0.011f, z - j);
            glVertex3f(x + i + tileSize, 0.011f, z - j - tileSize); glVertex3f(x + i, 0.011f, z - j - tileSize);
            glEnd();
            // Optional: Draw tile grid lines
            glDisable(GL_LIGHTING); glColor3f(0.7f, 0.7f, 0.7f);
            glBegin(GL_LINE_LOOP);
            glVertex3f(x + i, 0.012f, z - j); glVertex3f(x + i + tileSize, 0.012f, z - j);
            glVertex3f(x + i + tileSize, 0.012f, z - j - tileSize); glVertex3f(x + i, 0.012f, z - j - tileSize);
            glEnd(); glEnable(GL_LIGHTING);
        }
    }
}

void drawSoilPatch(float x, float z, float w, float l) {
    setMaterial(COL_SOIL); // Dark brown soil color
    glBegin(GL_QUADS); glNormal3f(0, 1, 0);
    glVertex3f(x, 0.008f, z); glVertex3f(x + w, 0.008f, z);
    glVertex3f(x + w, 0.008f, z - l); glVertex3f(x, 0.008f, z - l);
    glEnd();
}









void drawMarkings() {
    float y = Y_PAINT; setMaterial(COL_PAINT);
    float dLen=2.0f, gap=3.0f, dW=0.10f; 
    
    // Crosswalks (Zebras) - UPDATED to look like white stripes across the road
    // 1 Outside, 1 Before 1st, 1 After 1st, 1 After 2nd
    float crosses[] = {12.0f, -20.0f, -30.0f, -60.0f}; 
    float stripeW = 0.6f;
    float stripeGap = 0.4f; 
    float zWidth = 4.0f; // Width of the crosswalk area

    for(int c=0; c<4; c++) { 
        float zCenter = crosses[c]; 
        float zStart = zCenter - zWidth/2.0f;
        float zEnd = zCenter + zWidth/2.0f;

        // Draw stripes from left curb to right curb
        // Left Curb ~ 2.5f, Right Curb ~ 12.5f (Based on main road logic)
        for(float x = 2.5f; x < 12.5f; x += (stripeW + stripeGap)) {
            glBegin(GL_QUADS);
            glVertex3f(x, y, zStart); 
            glVertex3f(x + stripeW, y, zStart); 
            glVertex3f(x + stripeW, y, zEnd); 
            glVertex3f(x, y, zEnd); 
            glEnd();
        }
    } 

    // Dashed Lines (Main Road) - SPLIT INTO TWO LINES (Left Lane / Right Lane)
    float laneLeft = 4.75f;
    float laneRight = 10.25f;
    
    for(float z = 30.0f; z > -140.0f; z -= (dLen + gap)) {
        // Skip at Zebra locations
        bool skip = false;
        if(z < 14.0f && z > 10.0f) skip = true;
        if(z < -18.0f && z > -22.0f) skip = true;
        if(z < -28.0f && z > -32.0f) skip = true;
        if(z < -58.0f && z > -62.0f) skip = true;
        // Skip at Crossings
        if(z < -22.0f && z > -28.0f) skip = true;
        if(z < -52.0f && z > -58.0f) skip = true;
        
        if(skip) continue;

        // Draw Left Lane Divider
        glBegin(GL_QUADS);
        glVertex3f(laneLeft - dW, y, z); glVertex3f(laneLeft + dW, y, z);
        glVertex3f(laneLeft + dW, y, z - dLen); glVertex3f(laneLeft - dW, y, z - dLen);
        glEnd();

        // Draw Right Lane Divider
        glBegin(GL_QUADS);
        glVertex3f(laneRight - dW, y, z); glVertex3f(laneRight + dW, y, z);
        glVertex3f(laneRight + dW, y, z - dLen); glVertex3f(laneRight - dW, y, z - dLen);
        glEnd();
    }
}

void drawCurvedGreenery() {
    float y = 0.01f; float sZ = 0.5f; float maxArcDepth = 35.0f; float arcWidth = 40.0f; float straightLen = 150.0f; 
    glDisable(GL_LIGHTING); glColor3f(COL_GROUND.r, COL_GROUND.g, COL_GROUND.b); glBegin(GL_POLYGON); glNormal3f(0, 1, 0);
    glVertex3f(-220, y, 0); glVertex3f(-0.2f, y, sZ); for (float t = 0; t <= 1.0f; t += 0.05f) { float angle = t * (PI / 2.0f); float px = -0.2f - (arcWidth * sin(angle)); float pz = sZ + (maxArcDepth * (1.0f - cos(angle))); glVertex3f(px, y, pz); }
    float startX_L = -0.2f - arcWidth; float endX_L = startX_L - straightLen; glVertex3f(endX_L, y, sZ + maxArcDepth); glVertex3f(-220, y, 0); glEnd();
    glBegin(GL_POLYGON); glNormal3f(0, 1, 0); glVertex3f(220, y, 0); glVertex3f(15.6f, y, sZ); for (float t = 0; t <= 1.0f; t += 0.05f) { float angle = t * (PI / 2.0f); float px = 15.6f + (arcWidth * sin(angle)); float pz = sZ + (maxArcDepth * (1.0f - cos(angle))); glVertex3f(px, y, pz); }
    float startX_R = 15.6f + arcWidth; float endX_R = startX_R + straightLen; glVertex3f(endX_R, y, sZ + maxArcDepth); glVertex3f(220, y, 0); glEnd(); glEnable(GL_LIGHTING);
}

// --- FENCE STRUCTURE ---
void drawStoneBase(float length) { setMaterial(COL_FENCE_STONE); glPushMatrix(); glTranslatef(length / 2.0f, 0.2f, 0.0f); drawBox(length, 0.4f, 0.5f); glPopMatrix(); }
void drawConcreteWall(float length) { float wallH = 1.1f; float startY = 0.4f; setMaterial(COL_FENCE_CONC); glPushMatrix(); glTranslatef(length / 2.0f, startY + wallH / 2.0f, 0.0f); drawBox(length, wallH, 0.3f); glPopMatrix(); setMaterial(COL_FENCE_STRIPE); for(int i=1; i<=3; i++) { float stripeY = startY + (wallH * i / 4.0f); glPushMatrix(); glTranslatef(length/2.0f, stripeY, 0.0f); drawBox(length + 0.02f, 0.05f, 0.32f); glPopMatrix(); } }
void drawPillar() { float pH = 2.5f, pW = 0.8f, pD = 0.8f, holeW = 0.4f, holeH = 1.5f; setMaterial(COL_FENCE_PILLAR); glPushMatrix(); glTranslatef(-(pW-holeW)/4.0f - holeW/2.0f, pH/2.0f, 0.0f); drawBox((pW-holeW)/2.0f, pH, pD); glPopMatrix(); glPushMatrix(); glTranslatef((pW-holeW)/4.0f + holeW/2.0f, pH/2.0f, 0.0f); drawBox((pW-holeW)/2.0f, pH, pD); glPopMatrix(); glPushMatrix(); glTranslatef(0, (pH - holeH)/4.0f, 0); drawBox(holeW, (pH - holeH)/2.0f, pD); glPopMatrix(); glPushMatrix(); glTranslatef(0, pH - (pH - holeH)/4.0f, 0); drawBox(holeW, (pH - holeH)/2.0f, pD); glPopMatrix(); }
void drawMetalBars(float length) { int numBars = 4; float startY = 1.5f, endY = 2.4f; setMaterial(COL_FENCE_METAL); for(int i=0; i<numBars; i++) { float y = startY + (float)i * ((endY - startY) / numBars); glPushMatrix(); glTranslatef(length/2.0f, y + 0.1f, 0.0f); drawBox(length, 0.05f, 0.05f); glPopMatrix(); } }
void drawHalfStarShape(float outerR, float innerR, Color c) { glColor3f(c.r, c.g, c.b); glBegin(GL_LINE_STRIP); int steps = 60; float stepAngle = 180.0f / steps; for (int i = 0; i <= steps; i++) { float angleDeg = i * stepAngle; float angleRad = angleDeg * (PI / 180.0f); float wave = std::abs(sin(5.0f * angleRad)); float r = innerR + (outerR - innerR) * wave; glVertex3f(r * cos(angleRad), r * sin(angleRad), 0.0f); } glEnd(); }
void drawDecoration(float length) { float cx = length / 2.0f; float cy = 1.6f; glPushMatrix(); glTranslatef(cx, cy, 0.0f); glScalef(0.8f, 0.8f, 1.0f); Color dimWhite = { 0.85f, 0.85f, 0.85f }; glPushMatrix(); glTranslatef(0, 0, -0.02f); drawHalfStarShape(1.4f, 0.6f, dimWhite); glPopMatrix(); glPushMatrix(); glTranslatef(0, 0, 0.02f); drawHalfStarShape(0.9f, 0.35f, dimWhite); glPopMatrix(); glPopMatrix(); }
void drawFenceUnit(float length) { drawPillar(); glPushMatrix(); glTranslatef(0.4f, 0, 0); drawStoneBase(length - 0.8f); drawConcreteWall(length - 0.8f); drawMetalBars(length - 0.8f); drawDecoration(length - 0.8f); glPopMatrix(); }

void drawFenceWing(bool isRight) { 
    float sX=isRight?15.6f:-0.2f; float sZ=0.5f; float maxArcDepth = 35.0f; float arcWidth = 40.0f; float straightLen = 150.0f; int steps = 10; 
    for(int i=0; i<steps; i++) { float t1 = (float)i / steps; float t2 = (float)(i+1) / steps; float ang1 = t1 * (PI/2.0f); float ang2 = t2 * (PI/2.0f); float px1 = isRight ? sX + (arcWidth * sin(ang1)) : sX - (arcWidth * sin(ang1)); float pz1 = sZ + (maxArcDepth * (1.0f - cos(ang1))); float px2 = isRight ? sX + (arcWidth * sin(ang2)) : sX - (arcWidth * sin(ang2)); float pz2 = sZ + (maxArcDepth * (1.0f - cos(ang2))); float dx = px2 - px1; float dz = pz2 - pz1; float segLen = sqrt(dx*dx + dz*dz); float angle = atan2(dz, dx) * 180.0f / PI; glPushMatrix(); glTranslatef(px1, 0, pz1); glRotatef(-angle, 0, 1, 0); drawFenceUnit(segLen); glPopMatrix(); if(i%2==0) drawVariedPlant(px1, pz1 + 2.0f, i); else drawPencilTree(px1, pz1 + 2.0f); }
    float startX = isRight ? sX + arcWidth : sX - arcWidth; float zFlat = sZ + maxArcDepth; int straightUnits = (int)(straightLen / 6.0f); float unitLen = straightLen / straightUnits;
    for(int i=0; i<straightUnits; i++) { float cx = startX + (isRight ? 1.0f : -1.0f) * (i * unitLen); glPushMatrix(); glTranslatef(cx, 0, zFlat); if(!isRight) glRotatef(180, 0, 1, 0); drawFenceUnit(unitLen); glPopMatrix(); if(i%2==0) drawVariedPlant(cx, zFlat + 2.0f, i*10); else drawPencilTree(cx, zFlat + 2.0f); }
    setMaterial(COL_PARKING_LINE); float lineLen = 3.0f; float lineW = 0.2f; 
    for(float t=0.1f; t<=0.9f; t+=0.12f) { float angle = t * (PI/2.0f); float fx = isRight ? sX + (arcWidth * sin(angle)) : sX - (arcWidth * sin(angle)); float fz = sZ + (maxArcDepth * (1.0f - cos(angle))); float nX = sX - fx; float nZ = (sZ + maxArcDepth) - fz; float len = sqrt(nX*nX + nZ*nZ); nX /= len; nZ /= len; float startP_X = fx + nX * 1.0f; float startP_Z = fz + nZ * 1.0f; float endP_X = startP_X + nX * lineLen; float endP_Z = startP_Z + nZ * lineLen; glLineWidth(4.0f); glBegin(GL_QUADS); glVertex3f(startP_X - lineW, 0.03f, startP_Z - lineW); glVertex3f(startP_X + lineW, 0.03f, startP_Z + lineW); glVertex3f(endP_X + lineW, 0.03f, endP_Z + lineW); glVertex3f(endP_X - lineW, 0.03f, endP_Z - lineW); glEnd(); }
}
void drawStraightFenceSegment(float x1, float z1, float x2, float z2) { float dist = sqrt(pow(x2-x1,2) + pow(z2-z1,2)); float unitLen = 6.0f; int steps = (int)(dist / unitLen); unitLen = dist / steps; float angle = atan2(z2-z1, x2-x1) * 180.0f / PI; for(int i=0; i<steps; i++) { float t = (float)i/steps; float px = x1 + (x2-x1)*t; float pz = z1 + (z2-z1)*t; glPushMatrix(); glTranslatef(px, 0, pz); glRotatef(-angle, 0, 1, 0); drawFenceUnit(unitLen); glPopMatrix(); } }

void drawUniversityEnclosure() {
    float leftX = -190.2f; float rightX = 205.6f; float frontZ = 35.5f; float backZ = -200.0f;
    drawStraightFenceSegment(leftX, frontZ, leftX, backZ); drawStraightFenceSegment(rightX, frontZ, rightX, backZ); drawStraightFenceSegment(leftX, backZ, rightX, backZ);
}

void drawCobblestonePatch(float x, float z, float w, float h) {
    glNormal3f(0,1,0);
    float tileSize = 2.0f;
    for(float i=0; i<w; i+=tileSize) {
        for(float j=0; j<h; j+=tileSize) {
            Color c = ((int)((i+j)/tileSize)%2==0) ? COL_COBBLE : COL_PAVEMENT;
            setMaterial(c);
            glBegin(GL_QUADS);
            glVertex3f(x+i, Y_COBBLE, z-j);
            glVertex3f(x+i+tileSize, Y_COBBLE, z-j);
            glVertex3f(x+i+tileSize, Y_COBBLE, z-j-tileSize);
            glVertex3f(x+i, Y_COBBLE, z-j-tileSize);
            glEnd();
        }
    }
}

void drawOuterSpecificGeometry() {
    float roadY = Y_ROAD; float hwZ = 55.0f; float hwW = 10.0f; 
    setMaterial(COL_PAVEMENT); glBegin(GL_QUADS); glVertex3f(-1500.0f, -0.01f, 25.0f); glVertex3f(1500.0f, -0.01f, 25.0f); glVertex3f(1500.0f, -0.01f, 60.0f); glVertex3f(-1500.0f, -0.01f, 60.0f); glEnd();
    
    // Highway Road
    setMaterial(COL_ROAD); 
    glBegin(GL_QUADS); 
    glVertex3f(-1500, roadY, hwZ - hwW); glVertex3f(1500, roadY, hwZ - hwW); 
    glVertex3f(1500, roadY, hwZ + hwW); glVertex3f(-1500, roadY, hwZ + hwW); 
    glEnd();
    
    setMaterial(COL_BUS_BODY); glBegin(GL_QUADS); glVertex3f(-1500, roadY+0.01, hwZ - 0.2); glVertex3f(1500, roadY+0.01, hwZ - 0.2); glVertex3f(1500, roadY+0.01, hwZ + 0.2); glVertex3f(-1500, roadY+0.01, hwZ + 0.2); glEnd();
    
    // Main Entrance Road
    setMaterial(COL_ROAD); 
    float center = 6.75f; float roadWidth = 5.0f; float endZ = 35.5f; 
    glBegin(GL_QUADS); 
    glVertex3f(center - 0.5f - roadWidth, roadY, 0); glVertex3f(center - 0.5f, roadY, 0); glVertex3f(center - 0.5f, roadY, endZ); glVertex3f(center - 0.5f - roadWidth, roadY, endZ); 
    glVertex3f(center + 0.5f, roadY, 0); glVertex3f(center + 0.5f + roadWidth, roadY, 0); glVertex3f(center + 0.5f + roadWidth, roadY, endZ); glVertex3f(center + 0.5f, roadY, endZ); 
    glVertex3f(center - 0.5f, roadY, 0); glVertex3f(center + 0.5f, roadY, 0); glVertex3f(center + 0.5f, roadY, endZ); glVertex3f(center - 0.5f, roadY, endZ); 
    glEnd();
    
    // Parking Semi-Circle (Asphalt)
    float startFillZ = 28.0f; float sX_Right = 15.6f; float sX_Left = -0.2f; float sZ_Fence = 0.5f; float maxArcDepth = 35.0f; float arcWidth = 40.0f; float flatZ = sZ_Fence + maxArcDepth; 
    float roadEdgeL = center - 0.5f - roadWidth; 
    glBegin(GL_QUAD_STRIP); glNormal3f(0, 1, 0); 
    for(float z=startFillZ; z<=flatZ; z+=0.5f) { float ratio = (z - sZ_Fence) / maxArcDepth; if(ratio > 1.0f) ratio = 1.0f; float angle = acos(1.0f - ratio); float fenceX = sX_Left - (arcWidth * sin(angle)); glVertex3f(fenceX, roadY, z); glVertex3f(roadEdgeL, roadY, z); } 
    glEnd();
    float roadEdgeR = center + 0.5f + roadWidth; 
    glBegin(GL_QUAD_STRIP); glNormal3f(0, 1, 0); 
    for(float z=startFillZ; z<=flatZ; z+=0.5f) { float ratio = (z - sZ_Fence) / maxArcDepth; if(ratio > 1.0f) ratio = 1.0f; float angle = acos(1.0f - ratio); float fenceX = sX_Right + (arcWidth * sin(angle)); glVertex3f(roadEdgeR, roadY, z); glVertex3f(fenceX, roadY, z); } 
    glEnd();
    
    float countryRoadStart = hwZ - hwW; setMaterial(COL_WALKWAY); glBegin(GL_QUADS); glNormal3f(0, 1, 0); glVertex3f(-1500.0f, roadY+0.005f, flatZ); glVertex3f(1500.0f, roadY+0.005f, flatZ); glVertex3f(1500.0f, roadY+0.005f, countryRoadStart); glVertex3f(-1500.0f, roadY+0.005f, countryRoadStart); glEnd();
    for(float x = -150.0f; x <= 150.0f; x += 3.0f) { if(x > -10 && x < 25) continue; drawVariedPlant(x, countryRoadStart + 1.0f, (int)x); }
    glDisable(GL_LIGHTING); glColor3f(COL_GROUND.r, COL_GROUND.g, COL_GROUND.b); glBegin(GL_QUADS); glVertex3f(6.75f - 1.5f, 0.015f, -17.0f); glVertex3f(6.75f + 1.5f, 0.015f, -17.0f); glVertex3f(6.75f + 1.5f, 0.015f, -23.0f); glVertex3f(6.75f - 1.5f, 0.015f, -23.0f); glEnd();
    glPushMatrix(); glTranslatef(6.75f, 0.015f, -17.0f); drawSolidCircle2D(1.5f, COL_GROUND); glPopMatrix(); glPushMatrix(); glTranslatef(6.75f, 0.015f, -23.0f); drawSolidCircle2D(1.5f, COL_GROUND); glPopMatrix(); glEnable(GL_LIGHTING);
    drawTree(6.75f, -17.0f); drawTree(6.75f, -20.0f); drawTree(6.75f, -23.0f);
    for(int i=0; i<4; i++) { drawTree(-2.0f, 16.0f + (i * 2.5f)); } for(int i=0; i<4; i++) { drawTree(15.5f, 16.0f + (i * 2.5f)); }
}

void drawInnerCrossRoads() {
    float roadY = Y_ROAD; float w = 6.0f; setMaterial(COL_ROAD); 
    float dW = 0.15f; float dashLen = 1.0f; // For dashed center lines

    // --- Crossing 1 ---
    float z1 = -25.0f; 
    glBegin(GL_QUADS); glNormal3f(0,1,0); 
    glVertex3f(-100, roadY, z1 - w/2); glVertex3f(100, roadY, z1 - w/2); glVertex3f(100, roadY, z1 + w/2); glVertex3f(-100, roadY, z1 + w/2); 
    glEnd();
    for(float x=-80; x<=80; x+=25) { if(x>-10 && x<20) continue; drawStreetLight(x, z1 - w/2 - 1.0f, 0); } for(float x=-80; x<=80; x+=25) { if(x>-10 && x<20) continue; drawStreetLight(x, z1 + w/2 + 1.0f, 180); }
    // Middle dashed line for Crossing 1
    setMaterial(LOGO_WHITE);
    for(float x = -100; x < 100; x += 3.0f) {
        if(x > -10 && x < 25) continue; // Don't draw over main road intersection
        glBegin(GL_QUADS);
        glVertex3f(x, roadY + 0.005f, z1 - dW); glVertex3f(x + dashLen, roadY + 0.005f, z1 - dW);
        glVertex3f(x + dashLen, roadY + 0.005f, z1 + dW); glVertex3f(x, roadY + 0.005f, z1 + dW);
        glEnd();
    }

    // --- Crossing 2 ---
    setMaterial(COL_ROAD); 
    float z2 = -55.0f; 
    glBegin(GL_QUADS); glNormal3f(0,1,0); 
    glVertex3f(-100, roadY, z2 - w/2); glVertex3f(100, roadY, z2 - w/2); glVertex3f(100, roadY, z2 + w/2); glVertex3f(-100, roadY, z2 + w/2); 
    glEnd();
    for(float x=-80; x<=80; x+=25) { if(x>-10 && x<20) continue; drawStreetLight(x, z2 - w/2 - 1.0f, 0); } for(float x=-80; x<=80; x+=25) { if(x>-10 && x<20) continue; drawStreetLight(x, z2 + w/2 + 1.0f, 180); }
    // Middle dashed line for Crossing 2
    setMaterial(LOGO_WHITE);
    for(float x = -100; x < 100; x += 3.0f) {
        if(x > -10 && x < 25) continue;
        glBegin(GL_QUADS);
        glVertex3f(x, roadY + 0.005f, z2 - dW); glVertex3f(x + dashLen, roadY + 0.005f, z2 - dW);
        glVertex3f(x + dashLen, roadY + 0.005f, z2 + dW); glVertex3f(x, roadY + 0.005f, z2 + dW);
        glEnd();
    }

    // --- Crossing 3 (Back Highway / Road) ---
    // The main code draws "drawExtendedRoadNetwork" for z3 = -140. 
    // We will add the dashed line there in that function or here if we want to centralize.
    // For consistency with your request "all three crossing road", I will ensure ExtendedRoadNetwork has it.
}

void drawSpecificWalkway(bool isRight) { 
    float y=0.03f; float w=4.0f; float xBase = isRight ? 13.0f : 2.5f; setMaterial(COL_WALKWAY); 
    glBegin(GL_QUAD_STRIP); glNormal3f(0,1,0); for(float z=2.0f; z<=8.0f; z+=0.5f){ float t=(z-2.0f)/38.0f; float b=sin(t*PI)*5.0f; float iX=isRight?xBase+b:xBase-b; float oX=isRight?iX+w:iX-w; glVertex3f(iX,y,z); glVertex3f(oX,y,z); } glEnd();
    glBegin(GL_QUAD_STRIP); glNormal3f(0,1,0); for(float z=16.0f; z<=24.0f; z+=0.5f){ float t=(z-2.0f)/38.0f; float b=sin(t*PI)*5.0f; float iX=isRight?xBase+b:xBase-b; float oX=isRight?iX+w:iX-w; glVertex3f(iX,y,z); glVertex3f(oX,y,z); } glEnd();
}

// --- DYNAMIC ASSET HELPERS ---
void drawWheel(float x, float y, float z) {
    glPushMatrix(); glTranslatef(x, y, z); setMaterial(COL_IRON); 
    glutSolidTorus(0.12, 0.28, 8, 16); 
    setMaterial(COL_ARCH); glutSolidSphere(0.18, 8, 8); 
    glPopMatrix();
}

void drawRealCar(float x, float z, float angle, Color c) {
    glPushMatrix(); 
    glTranslatef(x, 0, z);
    glRotatef(angle, 0, 1, 0);
    glScalef(0.45f, 0.45f, 0.45f); 
    setMaterial(c); 
    glPushMatrix(); glTranslatef(0, 0.5f, 0); drawBox(2.2f, 0.6f, 4.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 1.0f, -0.2f); drawBox(1.9f, 0.7f, 2.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0.6f, 1.5f); drawBox(2.1f, 0.4f, 1.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0.6f, -1.8f); drawBox(2.1f, 0.4f, 1.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.7f, 0.5f, 2.21f); glColor3f(1, 1, 0.8f); glutSolidSphere(0.15, 8, 8); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.7f, 0.5f, 2.21f); glColor3f(1, 1, 0.8f); glutSolidSphere(0.15, 8, 8); glPopMatrix();
    drawWheel(1.1f, 0.35f, 1.3f); drawWheel(-1.1f, 0.35f, 1.3f); 
    drawWheel(1.1f, 0.35f, -1.3f); drawWheel(-1.1f, 0.35f, -1.3f);
    glPopMatrix();
}

void drawSUV(float x, float z, float angle) {
    glPushMatrix(); glTranslatef(x, 0, z); glRotatef(angle, 0, 1, 0); glScalef(0.5f, 0.5f, 0.5f);
    setMaterial(COL_PAINT); 
    glPushMatrix(); glTranslatef(0, 0.8f, 0); drawBox(2.4f, 0.8f, 4.6f); glPopMatrix(); 
    glPushMatrix(); glTranslatef(0, 1.6f, -0.2f); drawBox(2.2f, 0.8f, 3.0f); glPopMatrix(); 
    drawWheel(1.2f, 0.4f, 1.5f); drawWheel(-1.2f, 0.4f, 1.5f);
    drawWheel(1.2f, 0.4f, -1.5f); drawWheel(-1.2f, 0.4f, -1.5f);
    glPopMatrix();
}

void drawTruck(float x, float z, float angle) {
    glPushMatrix(); glTranslatef(x, 0, z); glRotatef(angle, 0, 1, 0); glScalef(0.6f, 0.6f, 0.6f);
    setMaterial(COL_SHIRT1); 
    glPushMatrix(); glTranslatef(0, 1.0f, 1.5f); drawBox(2.0f, 1.5f, 2.0f); glPopMatrix();
    setMaterial(COL_FENCE_CONC); 
    glPushMatrix(); glTranslatef(0, 1.2f, -1.5f); drawBox(2.2f, 1.8f, 4.0f); glPopMatrix();
    drawWheel(1.0f, 0.4f, 1.8f); drawWheel(-1.0f, 0.4f, 1.8f);
    drawWheel(1.0f, 0.4f, -0.5f); drawWheel(-1.0f, 0.4f, -0.5f);
    drawWheel(1.0f, 0.4f, -2.5f); drawWheel(-1.0f, 0.4f, -2.5f);
    glPopMatrix();
}

void drawSimpleBicycle() {
    Color silver = {0.7f, 0.7f, 0.75f};
    setMaterial(silver); glLineWidth(3.0f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(0, 0.4f, 0.6f); glutSolidTorus(0.05, 0.4, 6, 16); glPopMatrix(); 
    glPushMatrix(); glTranslatef(0, 0.4f, -0.6f); glutSolidTorus(0.05, 0.4, 6, 16); glPopMatrix();
    glColor3f(silver.r, silver.g, silver.b); 
    glBegin(GL_LINES); 
    glVertex3f(0, 0.4f, 0.6f); glVertex3f(0, 0.9f, 0.3f); 
    glVertex3f(0, 0.4f, -0.6f); glVertex3f(0, 0.9f, -0.3f); 
    glVertex3f(0, 0.9f, 0.3f); glVertex3f(0, 0.9f, -0.3f); 
    glVertex3f(0, 0.4f, 0); glVertex3f(0, 0.9f, 0.3f); 
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f); 
    glPushMatrix(); glTranslatef(0, 1.0f, 0.3f); glScalef(0.2f, 0.05f, 0.3f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(0, 1.0f, -0.3f); glRotatef(90, 0, 1, 0); glScalef(0.6f, 0.05f, 0.05f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(1, 0.8f, 0.6f); glPushMatrix(); glTranslatef(0, 1.5f, 0); glutSolidSphere(0.25f, 8, 8); glPopMatrix(); 
    glColor3f(0, 0, 1); glPushMatrix(); glTranslatef(0, 1.1f, 0); drawBox(0.4f, 0.5f, 0.2f); glPopMatrix();
}

void drawFountain(float x, float z) {
    glPushMatrix(); glTranslatef(x, 0, z);
    setMaterial(COL_FENCE_STONE);
    glPushMatrix(); glRotatef(-90,1,0,0); glutSolidTorus(0.3, 3.0, 10, 20); glPopMatrix(); // Basin
    setMaterial(LOGO_BLUE);
    glPushMatrix(); glTranslatef(0, 0.2f, 0); glScalef(2.8f, 0.1f, 2.8f); glutSolidSphere(1.0, 10, 10); glPopMatrix(); // Water
    setMaterial(COL_FENCE_PILLAR);
    glPushMatrix(); glRotatef(-90,1,0,0); gluCylinder(gluNewQuadric(), 0.5, 0.2, 2.0, 10, 2); glPopMatrix(); // Spout
    glPopMatrix();
}

// --- DYNAMIC LOGIC ---
void drawInternalTraffic() {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.05f; 
    float car1X = -100.0f + fmod(t, 200.0f);
    if(car1X > -90 && car1X < 90) drawRealCar(car1X, -25.0f - 2.0f, 90, COL_SHIRT1);
    float car2X = 100.0f - fmod(t + 50.0f, 200.0f);
    if(car2X > -90 && car2X < 90) drawRealCar(car2X, -25.0f + 2.0f, -90, COL_SHIRT2);
    float car3X = -100.0f + fmod(t + 100.0f, 200.0f);
    if(car3X > -90 && car3X < 90) drawRealCar(car3X, -55.0f - 2.0f, 90, COL_ARCH);
    float zDeep = -140.0f + fmod(t, 100.0f);
    if(zDeep > -140 && zDeep < -40) drawRealCar(5.25f, zDeep, 180, FL_SID_GRN);
}

void drawHighwayTraffic() {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.05f; float roadZ = 55.0f;
    for(int i=0; i<3; i++) { float offset = (i * 500.0f); float carX = -250.0f + fmod(t + offset, 500.0f); if(carX > -150 && carX < 150) {  Color c = (i%2==0) ? LOGO_RED : LOGO_BLUE; drawRealCar(carX, roadZ - 3.0f, 90, c); } }
    for(int i=0; i<3; i++) { float offset = (i * 600.0f); float carX = 250.0f - fmod(t + offset, 500.0f); if(carX > -150 && carX < 150) { Color c = (i%2==0) ? LOGO_GREEN : COL_ARCH; drawRealCar(carX, roadZ + 3.0f, -90, c); } }
    float busT = t * 0.8f;
    float bus1X = -100.0f + fmod(busT, 300.0f); if(bus1X > -150 && bus1X < 150) { glPushMatrix(); glTranslatef(bus1X, 0, roadZ - 6.0f); glRotatef(90, 0, 1, 0); drawBus(0,0,0); glPopMatrix(); }
    float bus2X = 100.0f - fmod(busT + 150.0f, 300.0f); if(bus2X > -150 && bus2X < 150) { glPushMatrix(); glTranslatef(bus2X, 0, roadZ + 6.0f); glRotatef(-90, 0, 1, 0); drawBus(0,0,0); glPopMatrix(); }
}

void drawTrafficSystem() {
    float timeVal = glutGet(GLUT_ELAPSED_TIME) * 0.015f; 
    float loopDist = 220.0f; 
    float zPos = 80.0f - fmod(timeVal, loopDist); 
    if(zPos > -140.0f) { drawRealCar(5.25f, zPos, 180.0f, FL_SID_RED); }
}

void drawParkedCars() {
    drawSUV(-18.0f, 6.0f, -70.0f); 
    drawTruck(-24.0f, 10.0f, -60.0f); 
    drawRealCar(18.0f, 6.0f, 70.0f, FL_TAXI_YEL); 
    drawBus(24.0f, 10.0f, 60.0f); 
}

void drawChildrenPlaying() {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.001f; 
    float fixedZ = 42.0f; 
    float centerX = 13.0f; 
    float centerX_2 = 2.0f;
    float range = 45.0f; 

    for(int i=0; i<3; i++) {
        float phase = i * 2.5f;
        float anim = t + phase;
        float currentX = centerX + sin(anim) * range;
        glPushMatrix(); glTranslatef(currentX, 0, fixedZ);
        float dir = cos(anim); if(dir > 0) glRotatef(90, 0, 1, 0); else glRotatef(270, 0, 1, 0);        
        drawSimpleBicycle(); glPopMatrix();
    }
}

void drawPerson(float x, float z, float angle, Color shirt) {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.01f;
    glPushMatrix(); glTranslatef(x, 0.9f, z); glRotatef(angle, 0, 1, 0); glScalef(0.6f, 0.6f, 0.6f);
    setMaterial(COL_PANTS); 
    glPushMatrix(); glTranslatef(-0.2f, -0.7f, 0); glRotatef(sin(t)*30, 1, 0, 0); drawBox(0.15f, 0.8f, 0.15f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.2f, -0.7f, 0); glRotatef(-sin(t)*30, 1, 0, 0); drawBox(0.15f, 0.8f, 0.15f); glPopMatrix();
    setMaterial(shirt); drawBox(0.5f, 0.8f, 0.25f);
    setMaterial(COL_SKIN); glPushMatrix(); glTranslatef(0, 0.6f, 0); glutSolidSphere(0.25f, 8, 8); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.35f, 0.1f, 0); glRotatef(-sin(t)*30, 1, 0, 0); drawBox(0.12f, 0.6f, 0.12f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.35f, 0.1f, 0); glRotatef(sin(t)*30, 1, 0, 0); drawBox(0.12f, 0.6f, 0.12f); glPopMatrix();
    glPopMatrix();
}

void drawPedestrians() {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.002f;
    float w1_z = 30.0f - fmod(t * 5.0f, 25.0f); drawPerson(11.5f, w1_z, 180, COL_SHIRT1);
    float w2_z = 2.0f - fmod(t * 5.0f + 10.0f, 40.0f); drawPerson(11.5f, w2_z, 180, COL_SHIRT2);
    float w3_z = 5.0f + fmod(t * 5.0f, 25.0f); drawPerson(2.0f, w3_z, 0, COL_SHIRT3);
    float sideX_R = 20.0f + fmod(t * 5.0f, 100.0f); drawPerson(sideX_R, 45.0f, 90, COL_SHIRT1);
    float sideX_L = -20.0f - fmod(t * 5.0f + 50.0f, 100.0f); drawPerson(sideX_L, 45.0f, 270, COL_SHIRT2);
    drawPerson(-10.0f, -40.0f + sin(t)*5.0f, 90, COL_SHIRT1);
    drawPerson(140.0f, -40.0f + cos(t)*5.0f, 270, COL_SHIRT2);
}
void drawCloud(float x, float y, float z, float speed) {
    float t = (float)glutGet(GLUT_ELAPSED_TIME) * 0.001f;
    // Clouds move across the sky and loop every 800 units
    float moveX = fmod(t * speed, 800.0f) - 400.0f;
    
    glPushMatrix();
    glTranslatef(x + moveX, y, z);
    
    glDisable(GL_LIGHTING); // Makes clouds "Glow" white against the blue sky
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Larger, fluffier cloud cluster
    glPushMatrix(); glScalef(1.5f, 1.0f, 1.0f); glutSolidSphere(6.0, 12, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(5.0f, -1.0f, 2.0f); glutSolidSphere(4.5, 12, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(-5.0f, -1.0f, 2.0f); glutSolidSphere(4.5, 12, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 2.0f, -1.0f); glutSolidSphere(4.0, 12, 12); glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawBird(float x, float y, float z, float speed) {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
    float flap = sin(t * 12.0f) * 25.0f; // Flapping frequency
    float moveZ = fmod(t * speed, 400.0f) - 200.0f; // Move along the road direction
    
    glPushMatrix();
    glTranslatef(x, y + sin(t*2.0f), z + moveZ); // Slight bobbing up and down
    setMaterial(COL_BIRD);
    
    // Left Wing
    glPushMatrix();
    glRotatef(flap, 0, 0, 1);
    glScalef(0.8f, 0.05f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Right Wing
    glPushMatrix();
    glRotatef(-flap, 0, 0, 1);
    glScalef(0.8f, 0.05f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void drawEagle(float radius, float y, float speed) {
    float t = (float)glutGet(GLUT_ELAPSED_TIME) * 0.001f * speed;
    // Eagle soars in a wide circle
    float ex = radius * cos(t);
    float ez = radius * sin(t);
    float flap = sin(t * 3.0f) * 10.0f; 

    glPushMatrix();
    glTranslatef(ex, y, ez);
    glRotatef(-t * 180.0f / (float)PI, 0, 1, 0); // Face the direction of flight
    
    setMaterial(COL_EAGLE);
    // Larger body
    glPushMatrix(); glScalef(0.6f, 0.3f, 1.2f); glutSolidCube(1.0); glPopMatrix();
    
    // Traditional C++98 loop for the two wings
    int sides[2]; 
    sides[0] = -1; 
    sides[1] = 1;
    
    for(int i = 0; i < 2; i++) {
        int side = sides[i];
        glPushMatrix();
        glRotatef((float)side * flap, 0, 0, 1);
        glTranslatef((float)side * 1.5f, 0, 0);
        glScalef(3.0f, 0.05f, 0.8f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    glPopMatrix();
}
void drawDynamicElements() {
    drawHighwayTraffic(); 
    drawTrafficSystem(); 
    drawInternalTraffic(); 
    drawChildrenPlaying(); 
    drawPedestrians();

    // --- AERIAL ELEMENTS SECTION ---

    // 1. MANY MOVING CLOUDS
    // We use a loop to spread them across the sky
    for(int i = 0; i < 15; i++) {
        // This spreads clouds at different X and Z positions
        float cloudX = -250.0f + (i * 40.0f); 
        float cloudZ = (i % 2 == 0) ? -50.0f : -150.0f; // Alternate depth
        float cloudY = 70.0f + (float)(i % 5) * 5.0f;  // Varying heights
        float cloudSpeed = 1.5f + (float)(i % 3);      // Different speeds
        
        drawCloud(cloudX, cloudY, cloudZ, cloudSpeed);
    }

    // 2. LARGE FLOCK OF BIRDS (Near the Main Road/Gate)
    // Flying in a "V" formation or group
    for(int j = 0; j < 10; j++) {
        float bx = 15.0f + (j * 2.0f);
        float by = 35.0f + (j % 3); 
        float bz = -20.0f - (j * 1.5f);
        drawBird(bx, by, bz, 18.0f); // Fast moving birds
    }
    
    // Another flock on the other side
    for(int j = 0; j < 8; j++) {
        float bx = -30.0f - (j * 2.5f);
        float by = 42.0f + (j % 2); 
        float bz = 10.0f + (j * 2.0f);
        drawBird(bx, by, bz, 12.0f);
    }

    // 3. MANY CIRCLING EAGLES
    // Multiple eagles at different radii and altitudes
    drawEagle(60.0f, 90.0f, 0.5f);   // Eagle 1
    drawEagle(90.0f, 100.0f, 0.4f);  // Eagle 2
    drawEagle(120.0f, 115.0f, 0.3f); // Eagle 3
    drawEagle(150.0f, 130.0f, 0.25f);// Eagle 4
    drawEagle(40.0f, 85.0f, 0.6f);   // Eagle 5 (Smaller circle)
}

void drawInternalParkAreas() {
    float lx = -55.0f, lz = -80.0f;
    drawCobblestonePatch(lx-15.0f, lz+10.0f, 40.0f, 40.0f);
    drawTable(lx, lz); drawTable(lx - 8.0f, lz - 5.0f); drawTable(lx + 8.0f, lz - 5.0f);
    drawTree(lx - 12.0f, lz); drawTree(lx + 8.0f, lz + 8.0f);

    float rx = 55.0f, rz = -80.0f;
    drawCobblestonePatch(rx-10.0f, rz+10.0f, 40.0f, 40.0f);
    drawFountain(rx, rz);
    drawBench(rx + 10.0f, rz + 5.0f, 45); drawBench(rx - 10.0f, rz + 5.0f, -45);
    setMaterial(LOGO_BLUE); glPushMatrix(); glTranslatef(rx+15.0f, 0, rz-5.0f); glRotatef(-90,1,0,0); glutSolidCone(0.5, 3.0, 10, 2); glPopMatrix();
    setMaterial(LOGO_RED);  glPushMatrix(); glTranslatef(rx+15.0f, 1.5f, rz-3.5f); glRotatef(45, 1, 0, 0); drawBox(1.0f, 4.0f, 0.1f); glPopMatrix();
    drawVariedPlant(rx - 8.0f, rz-8.0f, 1); drawVariedPlant(rx + 12.0f, rz-8.0f, 2);
}



void drawHousePlot(float x, float z, float angle, int seed) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(angle, 0, 1, 0);

    float sizeScale = 0.7f + (float)(seed % 5) * 0.15f;
    float plotW = 12.0f * sizeScale;
    float plotD = 12.0f * sizeScale;

    // --- VARIED GROUND COLOR LOGIC ---
    // We choose ground based on the seed
    if (seed % 4 == 0) {
        setMaterial(COL_GROUND);   // Green Yard
    } else if (seed % 4 == 1) {
        setMaterial(COL_SOIL);     // Brown Soil Yard
    } else if (seed % 4 == 2) {
        setMaterial(COL_PAVEMENT); // Grey Concrete Yard
    } else {
        Color sandy = {0.8f, 0.7f, 0.5f}; // Sandy/Dry Ground
        setMaterial(sandy);
    }

    // Draw Yard at Y=0.005 to prevent flickering with the grey city floor
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-plotW/2, 0.005f, -plotD/2);
    glVertex3f(plotW/2, 0.005f, -plotD/2);
    glVertex3f(plotW/2, 0.005f, plotD/2);
    glVertex3f(-plotW/2, 0.005f, plotD/2);
    glEnd();

    // House Fence
    if (seed % 3 == 0) {
        setMaterial(COL_FENCE_STONE);
        float fH = 0.8f;
        glPushMatrix(); glTranslatef(-plotW/4, fH/2, plotD/2); drawBox(plotW/2, fH, 0.2f); glPopMatrix(); 
        glPushMatrix(); glTranslatef(plotW/2, fH/2, 0); drawBox(0.2f, fH, plotD); glPopMatrix();
        glPushMatrix(); glTranslatef(-plotW/2, fH/2, 0); drawBox(0.2f, fH, plotD); glPopMatrix();
    }

    glScalef(sizeScale, sizeScale, sizeScale);
    drawVariedHouse(0, 0, 0, seed); 
    glPopMatrix();
}











void drawSurroundingCity() {
    float roadY = 0.02f;
    
    // --- 1. CITY STREETS (Infrastructure) ---
    setMaterial(COL_ROAD);

    // Vertical Streets (Only outside the university's left and right sides)
    for(float x = -400; x <= 400; x += 60) {
        // Horizontal protection: If X is in university range, streets only draw in Front or Back
        bool inUnivX = (x > -200 && x < 220);
        
        glBegin(GL_QUADS);
        if (!inUnivX) {
            // Full street from far front to far back
            glVertex3f(x-2, roadY, -500); glVertex3f(x+2, roadY, -500);
            glVertex3f(x+2, roadY, 500);  glVertex3f(x-2, roadY, 500);
        } else {
            // Split street: Part in Front, Part in Back
            glVertex3f(x-2, roadY, 70);   glVertex3f(x+2, roadY, 70);   // Front segment
            glVertex3f(x+2, roadY, 500);  glVertex3f(x-2, roadY, 500);
            
            glVertex3f(x-2, roadY, -500); glVertex3f(x+2, roadY, -500); // Back segment
            glVertex3f(x+2, roadY, -210); glVertex3f(x-2, roadY, -210);
        }
        glEnd();
    }

    // Horizontal Streets
    for(float z = -450; z <= 450; z += 50) {
        // Skip the main highway (z=55) and the internal university range
        if (z > 40 && z < 70) continue; 
        bool inUnivZ = (z > -210 && z < 40);

        glBegin(GL_QUADS);
        if (!inUnivZ) {
            // Wide street passing in front or behind the university
            glVertex3f(-500, roadY, z-2); glVertex3f(500, roadY, z-2);
            glVertex3f(500, roadY, z+2);  glVertex3f(-500, roadY, z+2);
        } else {
            // Street stops at university walls
            glVertex3f(-500, roadY, z-2); glVertex3f(-200, roadY, z-2); // Left side
            glVertex3f(-200, roadY, z+2); glVertex3f(-500, roadY, z+2);
            
            glVertex3f(220, roadY, z-2);  glVertex3f(500, roadY, z-2);  // Right side
            glVertex3f(500, roadY, z+2);  glVertex3f(220, roadY, z+2);
        }
        glEnd();
    }

    // --- 2. HOUSE PLOTS (Neighborhoods) ---

    // ZONE: LEFT SIDE (X < -210)
    for(float x = -400; x <= -220; x += 35) {
        for(float z = -450; z <= 450; z += 35) {
            if (z > 40 && z < 70) continue; // Skip highway
            drawHousePlot(x, z, 90, (int)(abs(x)+abs(z)));
        }
    }

    // ZONE: RIGHT SIDE (X > 220)
    for(float x = 230; x <= 450; x += 35) {
        for(float z = -450; z <= 450; z += 35) {
            if (z > 40 && z < 70) continue; // Skip highway
            drawHousePlot(x, z, -90, (int)(abs(x)+abs(z)));
        }
    }

    // ZONE: FRONT (In front of the highway, z > 80)
    for(float x = -190; x <= 210; x += 40) {
        for(float z = 80; z <= 450; z += 35) {
            drawHousePlot(x, z, 180, (int)(x+z));
        }
    }

    // ZONE: BACK (Behind the back fence, z < -220)
    for(float x = -190; x <= 210; x += 40) {
        for(float z = -450; z <= -220; z += 35) {
            drawHousePlot(x, z, 0, (int)(x+z));
        }
    }
}












void drawRightDorms() {
    float startZ = -40.0f; float xPos = 145.0f;
    for(int i=0; i<3; i++) { drawBuildingWithWalkway(xPos, startZ - (i * 45.0f), 4, 18.0f, 30.0f, COL_BLD_BRICK); }
}

void drawExtendedRoadNetwork() {
    float roadY = Y_ROAD; float w = 6.0f; float dashW = 0.2f; float walkW = 2.5f;   
    float xSide = 115.0f; float z3 = -140.0f; float zStart = -20.0f; float zEnd = -160.0f;    
    setMaterial(COL_ROAD); glBegin(GL_QUADS); glNormal3f(0,1,0);
    glVertex3f(-xSide - w/2 - 2.0f, roadY, z3 - w/2); glVertex3f(xSide + w/2 + 2.0f, roadY, z3 - w/2); glVertex3f(xSide + w/2 + 2.0f, roadY, z3 + w/2); glVertex3f(-xSide - w/2 - 2.0f, roadY, z3 + w/2);
    glVertex3f(-xSide - w/2, roadY, zStart); glVertex3f(-xSide + w/2, roadY, zStart); glVertex3f(-xSide + w/2, roadY, zEnd); glVertex3f(-xSide - w/2, roadY, zEnd);
    glVertex3f(xSide - w/2, roadY, zStart); glVertex3f(xSide + w/2, roadY, zStart); glVertex3f(xSide + w/2, roadY, zEnd); glVertex3f(xSide - w/2, roadY, zEnd);
    float cZ1 = -25.0f; float cZ2 = -55.0f;
    glVertex3f(-100.0f, roadY, cZ1 - w/2); glVertex3f(-xSide, roadY, cZ1 - w/2); glVertex3f(-xSide, roadY, cZ1 + w/2); glVertex3f(-100.0f, roadY, cZ1 + w/2);
    glVertex3f(-100.0f, roadY, cZ2 - w/2); glVertex3f(-xSide, roadY, cZ2 - w/2); glVertex3f(-xSide, roadY, cZ2 + w/2); glVertex3f(-100.0f, roadY, cZ2 + w/2);
    glVertex3f(100.0f, roadY, cZ1 - w/2); glVertex3f(xSide, roadY, cZ1 - w/2); glVertex3f(xSide, roadY, cZ1 + w/2); glVertex3f(100.0f, roadY, cZ1 + w/2);
    glVertex3f(100.0f, roadY, cZ2 - w/2); glVertex3f(xSide, roadY, cZ2 - w/2); glVertex3f(xSide, roadY, cZ2 + w/2); glVertex3f(100.0f, roadY, cZ2 + w/2);
    glEnd();
    setMaterial(COL_WALKWAY); glBegin(GL_QUADS); glNormal3f(0,1,0);
    glVertex3f(-xSide - w/2, roadY, z3 - w/2); glVertex3f(xSide + w/2, roadY, z3 - w/2); glVertex3f(xSide + w/2, roadY, z3 - w/2 - walkW); glVertex3f(-xSide - w/2, roadY, z3 - w/2 - walkW);
    glVertex3f(-xSide - w/2, roadY, z3 + w/2); glVertex3f(xSide + w/2, roadY, z3 + w/2); glVertex3f(xSide + w/2, roadY, z3 + w/2 + walkW); glVertex3f(-xSide - w/2, roadY, z3 + w/2 + walkW);
    glVertex3f(-xSide - w/2, roadY, zStart); glVertex3f(-xSide - w/2 - walkW, roadY, zStart); glVertex3f(-xSide - w/2 - walkW, roadY, zEnd); glVertex3f(-xSide - w/2, roadY, zEnd);
    glVertex3f(-xSide + w/2, roadY, zStart); glVertex3f(-xSide + w/2 + walkW, roadY, zStart); glVertex3f(-xSide + w/2 + walkW, roadY, zEnd); glVertex3f(-xSide + w/2, roadY, zEnd);
    glVertex3f(xSide - w/2, roadY, zStart); glVertex3f(xSide - w/2 - walkW, roadY, zStart); glVertex3f(xSide - w/2 - walkW, roadY, zEnd); glVertex3f(xSide - w/2, roadY, zEnd);
    glVertex3f(xSide + w/2, roadY, zStart); glVertex3f(xSide + w/2 + walkW, roadY, zStart); glVertex3f(xSide + w/2 + walkW, roadY, zEnd); glVertex3f(xSide + w/2, roadY, zEnd);
    glEnd();

    for(float x = -xSide; x <= xSide; x += 2.0f) {
        if((int)abs(x) % 4 == 0) { setMaterial(LOGO_WHITE); glBegin(GL_QUADS); glVertex3f(x, roadY+0.005f, z3 - dashW); glVertex3f(x+1.5f, roadY+0.005f, z3 - dashW); glVertex3f(x+1.5f, roadY+0.005f, z3 + dashW); glVertex3f(x, roadY+0.005f, z3 + dashW); glEnd(); }
        if((int)abs(x) % 15 == 0 && abs(x - 6.75f) > 8.0f) { drawTree(x, z3 - w/2 - 3.0f); drawTree(x, z3 + w/2 + 3.0f); if((int)abs(x) % 30 == 0) drawStreetLight(x, z3 - w/2 - 3.0f, 0); else drawStreetLight(x, z3 + w/2 + 3.0f, 180); }
    }
    for(float z = zStart; z > zEnd; z -= 2.0f) {
        // Prevent white dashes from drawing over the 2nd crossing (-55)
        if(z < -52.0f && z > -58.0f) continue; 
        
        if((int)abs(z) % 4 == 0) { setMaterial(LOGO_WHITE); glBegin(GL_QUADS); glVertex3f(-xSide - dashW, roadY+0.005f, z); glVertex3f(-xSide + dashW, roadY+0.005f, z); glVertex3f(-xSide + dashW, roadY+0.005f, z - 1.5f); glVertex3f(-xSide - dashW, roadY+0.005f, z - 1.5f); glEnd(); }
        if((int)abs(z) % 12 == 0) { drawTree(-xSide - w/2 - 3.5f, z); drawTree(-xSide + w/2 + 3.5f, z); if((int)abs(z) % 24 == 0) drawStreetLight(-xSide - w/2 - 3.5f, z, 90); else drawStreetLight(-xSide + w/2 + 3.5f, z, -90); }
    }
    for(float z = zStart; z > zEnd; z -= 2.0f) {
        if(z < -52.0f && z > -58.0f) continue;
        
        if((int)abs(z) % 4 == 0) { setMaterial(LOGO_WHITE); glBegin(GL_QUADS); glVertex3f(xSide - dashW, roadY+0.005f, z); glVertex3f(xSide + dashW, roadY+0.005f, z); glVertex3f(xSide + dashW, roadY+0.005f, z - 1.5f); glVertex3f(xSide - dashW, roadY+0.005f, z - 1.5f); glEnd(); }
        if((int)abs(z) % 12 == 0) { drawTree(xSide - w/2 - 3.5f, z); drawTree(xSide + w/2 + 3.5f, z); if((int)abs(z) % 24 == 0) drawStreetLight(xSide - w/2 - 3.5f, z, 90); else drawStreetLight(xSide + w/2 + 3.5f, z, -90); }
    }
    // Added Dashed Line to 3rd Crossing (Back road z3 = -140)
    setMaterial(LOGO_WHITE);
    float z3c = -140.0f;
    for(float x = -xSide; x < xSide; x += 3.0f) {
        if(x > -10 && x < 25) continue;
        glBegin(GL_QUADS);
        glVertex3f(x, roadY + 0.005f, z3c - dashW); glVertex3f(x + 1.0f, roadY + 0.005f, z3c - dashW);
        glVertex3f(x + 1.0f, roadY + 0.005f, z3c + dashW); glVertex3f(x, roadY + 0.005f, z3c + dashW);
        glEnd();
    }
}

// --- MAIN LANDSCAPE ---
void drawDetailedLandscape() {
    float roadY = Y_ROAD; 
    glDisable(GL_LIGHTING);
// 1. Main Background (City Concrete - Absolute Bottom Layer)
    glColor3f(COL_CITY_GND.r, COL_CITY_GND.g, COL_CITY_GND.b); 
    glBegin(GL_QUADS); 
        glNormal3f(0, 1, 0); 
        glVertex3f(-1500.0f, 0.0f, -1500.0f); 
        glVertex3f(-1500.0f, 0.0f, 1500.0f); 
        glVertex3f(1500.0f, 0.0f, 1500.0f); 
        glVertex3f(1500.0f, 0.0f, -1500.0f); 
    glEnd();
    // 2. Green Patches (Inside Main Campus)
    glColor3f(COL_GROUND.r, COL_GROUND.g, COL_GROUND.b); glBegin(GL_QUADS); glNormal3f(0,1,0);
    glVertex3f(-220, Y_GROUND+0.005f, -1500); glVertex3f(-220, Y_GROUND+0.005f, 0); glVertex3f(220, Y_GROUND+0.005f, 0); glVertex3f(220, Y_GROUND+0.005f, -1500);
    glEnd();
    
    glEnable(GL_LIGHTING);
    
    
    
    // --- MIXED GROUND TEXTURES ---
    
    // 1. Ceramic Plazas (Around the buildings to the left and right of the gate)
    drawCeramicPatch(-45.0f, -30.0f, 40.0f, 35.0f); // Left Plaza
    drawCeramicPatch(18.0f, -30.0f, 45.0f, 35.0f);  // Right Plaza

    // 2. Soil Areas (Under the trees lining the main road)
    drawSoilPatch(0.5f, 0.0f, 2.0f, 140.0f);  // Soil strip left of road
    drawSoilPatch(12.5f, 0.0f, 2.0f, 140.0f); // Soil strip right of road

    // 3. Cobblestone walk-paths (In the student park areas)
    drawCobblestonePatch(-100.0f, -10.0f, 60.0f, 20.0f); // Left Path
    drawCobblestonePatch(40.0f, -10.0f, 60.0f, 20.0f);   // Right Path

    // 4. Large Ceramic area near the Dormitories
    drawCeramicPatch(135.0f, -30.0f, 35.0f, 120.0f);
    
    
    
    
    // Main Road (Drawn last to be on top)
    float mainRoadEnd = -144.0f;
    setMaterial(COL_ROAD); glBegin(GL_QUADS); glNormal3f(0,1,0); glVertex3f(2.0f, roadY, 0); glVertex3f(13.0f, roadY, 0); glVertex3f(13.0f, roadY, mainRoadEnd); glVertex3f(2.0f, roadY, mainRoadEnd); glEnd();

    drawInnerCrossRoads(); drawExtendedRoadNetwork(); drawRightDorms();
    drawParkedCars();
    drawInternalParkAreas(); 
    drawSurroundingCity();   

    setMaterial(COL_PAVEMENT); glBegin(GL_QUADS); glNormal3f(0,1,0); float paveEnd = 28.0f; glVertex3f(-1500, roadY-0.005f, 0); glVertex3f(-1500, roadY-0.005f, paveEnd); glVertex3f(1500, roadY-0.005f, paveEnd); glVertex3f(1500, roadY-0.005f, 0); glEnd();
    drawCurvedGreenery(); drawOuterSpecificGeometry(); drawMarkings(); drawUniversityEnclosure(); 

    float wY = 0.028f; setMaterial(COL_WALKWAY); glBegin(GL_QUADS); glVertex3f(0.5f,wY,2.0f); glVertex3f(3.5f,wY,2.0f); glVertex3f(3.5f,wY,mainRoadEnd); glVertex3f(0.5f,wY,mainRoadEnd); glVertex3f(10.0f,wY,2.0f); glVertex3f(13.0f,wY,2.0f); glVertex3f(13.0f,wY,mainRoadEnd); glVertex3f(10.0f,wY,mainRoadEnd); glEnd();
    drawPlanterWithShrubs(-2.0f, 19.75f, 1.5f, 9.0f, 4); drawPlanterWithShrubs(15.5f, 19.75f, 1.5f, 9.0f, 4);
    for(int i=0; i<6; i++) { float rz = -5.0f - (i * 2.5f); drawBench(0.5f, rz - 1.0f, 45.0f + i*10.0f); drawBench(13.0f, rz - 1.0f, -45.0f - i*10.0f); }
    
    // Parking Area (Semi-Circle)
    setMaterial(COL_ROAD); glBegin(GL_QUADS); glVertex3f(15.0f,roadY,-5.0f); glVertex3f(29.0f,roadY,-5.0f); glVertex3f(29.0f,roadY,-22.0f); glVertex3f(15.0f,roadY,-22.0f); glEnd();

    drawBus(18.5f,-8.0f,15.0f); drawBus(18.5f,-16.0f,-15.0f); drawCircularSeat(26.0f,-10.0f); drawCircularSeat(22.0f,-18.0f);  
    drawBuildingWithWalkway(-15.0f,-40.0f,5,8.0f,10.0f,COL_BLD_BLUE); drawBuildingWithWalkway(-32.0f,-40.0f,3,10.0f,10.0f,COL_BLD_BRICK); drawBuildingWithWalkway(28.0f,-40.0f,4,8.0f,10.0f,COL_BLD_BEIGE); drawBuildingWithWalkway(50.0f,-40.0f,3,12.0f,10.0f,COL_BLD_GREY); 
    drawBuildingWithWalkway(-85.0f, -120, 6, 40, 20, COL_BLD_BLUE); drawBuildingWithWalkway(-60, -90, 4, 15, 40, COL_BLD_BRICK); drawBuildingWithWalkway(-90, -110, 4, 15, 40, COL_BLD_BEIGE); drawBuildingWithWalkway(60, -90, 4, 15, 40, COL_BLD_BRICK); drawBuildingWithWalkway(90, -110, 4, 15, 40, COL_BLD_BEIGE);
    for(int k=0; k<4; k++) { drawBuildingWithWalkway(-160.0f, -80.0f - (k * 35.0f), 3, 15.0f, 25.0f, COL_BLD_BRICK); }
    drawPlanterWithShrubs(6.75f, 20.0f, 2.0f, 14.0f, 2); 
    
    float center = 6.75f; float cZ1=-25.0f, cZ2=-55.0f;
    for(float z=-5; z>-70; z-=5) { if(z<cZ1+4&&z>cZ1-4) continue; if(z<cZ2+4&&z>cZ2-4) continue; drawTree(center, z); }
    for(float z=-5; z > -140.0f; z-=3.5f) { if(z<-21 && z>-29) continue; if(z<-51 && z>-59) continue; drawTree(1.5f, z); drawTree(12.0f,z); }
    
    float fInner = -21.5f; 
    drawFlag(-18.0f, fInner, 5.0f, 0); 
    drawFlag(-10.0f, fInner, 5.0f, 0); 
    drawFlag(20.0f, fInner, 5.0f, 0);  
    drawFlag(28.0f, fInner, 5.0f, 0);  
    drawFlag(-26.0f, fInner, 5.0f, 1);
    drawFlag(36.0f, fInner, 5.0f, 1);

    for(float z=-90; z > -140; z -= 15) { drawStreetLight(1.5f, z, 0); } for(float z=-90; z > -140; z -= 15) { drawStreetLight(12.0f, z, 180); }
    for(float z=-90; z<30; z+=15) { drawStreetLight(1.5f, z, 0); } for(float z=-90; z<30; z+=15) { drawStreetLight(12.0f, z, 180); }
    for(float x=-140; x<140; x+=25) { if(x>-20 && x<30) continue; drawStreetLight(x, 43.0f, 0); } for(float x=-140; x<140; x+=25) { if(x>-20 && x<30) continue; drawStreetLight(x, 67.0f, 180); }
}

void drawLogoOnWall(float cx, float cy) { float z=GATE_DEPTH/2.0f+0.02f; glPushMatrix(); glTranslatef(cx,cy,z); glScalef(0.45f, 0.45f, 1.0f); drawDetailedLogoGeometry(1.0f); glPopMatrix(); }
void draw3DArch(float cx, float r) { float rO=r, rI=r-ARCH_THICKNESS; int s=60; float hD=GATE_DEPTH/2; setMaterial(COL_ARCH); glBegin(GL_TRIANGLE_STRIP); glNormal3f(0,0,1); for(int i=0;i<=s;i++){float t=PI*i/s;glVertex3f(cx+rI*cos(t),rI*sin(t),hD);glVertex3f(cx+rO*cos(t),rO*sin(t),hD);} glEnd(); glBegin(GL_TRIANGLE_STRIP); glNormal3f(0,0,-1); for(int i=0;i<=s;i++){float t=PI*i/s;glVertex3f(cx+rO*cos(t),rO*sin(t),-hD);glVertex3f(cx+rI*cos(t),rI*sin(t),-hD);} glEnd(); setMaterial(COL_ARCH_OUT); glBegin(GL_QUAD_STRIP); for(int i=0;i<=s;i++){float t=PI*i/s;glNormal3f(cos(t),sin(t),0);glVertex3f(cx+rO*cos(t),rO*sin(t),hD);glVertex3f(cx+rO*cos(t),rO*sin(t),-hD);} glEnd(); glBegin(GL_QUAD_STRIP); for(int i=0;i<=s;i++){float t=PI*i/s;glNormal3f(-cos(t),-sin(t),0);glVertex3f(cx+rI*cos(t),rI*sin(t),-hD);glVertex3f(cx+rI*cos(t),rI*sin(t),hD);} glEnd(); }
void draw3DLeftWall() { float cxA=2.25f, rA=2.25f-ARCH_THICKNESS; float cxB=6.20f, rB=3.80f; float ix=solveIntersection(cxA, rA, cxB, rB); float drawEnd=ix; float halfD=GATE_DEPTH/2.0f; setMaterial(COL_WALL); glBegin(GL_QUAD_STRIP); glNormal3f(0,0,1); for(float x=0;x<=drawEnd;x+=0.05f){float h=std::max(getCircleY(x, cxA, rA), getCircleY(x, cxB, rB)); if(h>0) h+=WALL_EPS; glVertex3f(x,0,halfD); glVertex3f(x,h,halfD);} float fH=std::max(getCircleY(drawEnd,cxA,rA), getCircleY(drawEnd,cxB,rB))+WALL_EPS; glVertex3f(drawEnd,0,halfD); glVertex3f(drawEnd,fH,halfD); glEnd(); glBegin(GL_QUAD_STRIP); glNormal3f(0,0,-1); for(float x=0;x<=drawEnd;x+=0.05f){float h=std::max(getCircleY(x, cxA, rA), getCircleY(x, cxB, rB)); if(h>0) h+=WALL_EPS; glVertex3f(x,h,-halfD); glVertex3f(x,0,-halfD);} glVertex3f(drawEnd,fH,-halfD); glVertex3f(drawEnd,0,-halfD); glEnd(); glBegin(GL_QUAD_STRIP); glNormal3f(0,1,0); for(float x=0;x<=drawEnd;x+=0.05f){float h=std::max(getCircleY(x, cxA, rA), getCircleY(x, cxB, rB)); if(h>0) h+=WALL_EPS; glVertex3f(x,h,halfD); glVertex3f(x,h,-halfD);} glVertex3f(drawEnd,fH,halfD); glVertex3f(drawEnd,fH,-halfD); glEnd();}
void draw3DRightWall() { float cxD=12.7f, rD=2.70f-ARCH_THICKNESS; float cxC=8.00f, rC=4.60f; float ds=solveIntersection(cxD, rD, cxC, rC); float halfD=GATE_DEPTH/2.0f; setMaterial(COL_WALL); float sH=std::max(getCircleY(ds,cxD,rD), getCircleY(ds,cxC,rC))+WALL_EPS; glBegin(GL_QUAD_STRIP); glNormal3f(0,0,1); glVertex3f(ds,0,halfD); glVertex3f(ds,sH,halfD); for(float x=ds+0.05f;x<=15.4f;x+=0.05f){float h=std::max(getCircleY(x, cxD, rD), getCircleY(x, cxC, rC)); if(h>0) h+=WALL_EPS; glVertex3f(x,0,halfD); glVertex3f(x,h,halfD);} glEnd(); glBegin(GL_QUAD_STRIP); glNormal3f(0,0,-1); glVertex3f(ds,sH,-halfD); glVertex3f(ds,0,-halfD); for(float x=ds+0.05f;x<=15.4f;x+=0.05f){float h=std::max(getCircleY(x, cxD, rD), getCircleY(x, cxC, rC)); if(h>0) h+=WALL_EPS; glVertex3f(x,h,-halfD); glVertex3f(x,0,-halfD);} glEnd(); glBegin(GL_QUAD_STRIP); glNormal3f(0,1,0); glVertex3f(ds,sH,halfD); glVertex3f(ds,sH,-halfD); for(float x=ds+0.05f;x<=15.4f;x+=0.05f){float h=std::max(getCircleY(x, cxD, rD), getCircleY(x, cxC, rC)); if(h>0) h+=WALL_EPS; glVertex3f(x,h,halfD); glVertex3f(x,h,-halfD);} glEnd();}
void drawRungs3D() { int c=8; float rW=0.15f; float sX=6.6f,eX=9.6f; float cB=6.2f,rB=3.8f; float cC=8.0f,rC=4.6f-ARCH_THICKNESS; float zMx=0.3f; setMaterial(COL_RUNG); for(int i=0;i<c;i++){float t=(float)i/(c-1);float x1=sX+t*(eX-sX);float y1=getCircleY(x1,cB,rB);float vx=x1-cB;float vy=y1;float len=sqrt(vx*vx+vy*vy);float dx=vx/len;float dy=vy/len;float dif=cB-cC;float A=1;float B=2*dif*dx;float C=dif*dif-rC*rC;float d=B*B-4*A*C;if(d>=0){float dist=(-B+sqrt(d))/(2*A);float x2=cB+dist*dx;float y2=dist*dy;float nx=-dy*(rW/2),ny=dx*(rW/2);glBegin(GL_QUADS);glNormal3f(0,0,1);glVertex3f(x1-nx,y1-ny,zMx);glVertex3f(x2-nx,y2-ny,zMx);glVertex3f(x2+nx,y2+ny,zMx);glVertex3f(x1+nx,y1+ny,zMx);glNormal3f(0,1,0);glVertex3f(x1+nx,y1+ny,zMx);glVertex3f(x2+nx,y2+ny,zMx);glVertex3f(x2+nx,y2+ny,-zMx);glVertex3f(x1+nx,y1+ny,-zMx);glEnd();}}}

void idle() { glutPostRedisplay(); }
void keyboard(unsigned char key, int x, int y) { float s=1.0f; switch(key) { case 'w': camZ-=s; break; case 's': camZ+=s; break; case 'a': camX-=s; break; case 'd': camX+=s; break; case 'q': camY+=s; break; case 'e': camY-=s; break; case 27: exit(0); } }

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
    gluLookAt(camX, camY, camZ, 7.25, 1.0, -15.0, 0.0, 1.0, 0.0);
    GLfloat lp[]={10.0f, 50.0f, 40.0f, 1.0f}; glLightfv(GL_LIGHT0, GL_POSITION, lp);
    drawDetailedLandscape();
    draw3DArch(11.25f,1.25f); draw3DArch(6.2f,3.8f); draw3DArch(12.7f,2.7f); draw3DArch(2.25f,2.25f); draw3DArch(8.0f,4.6f);
    draw3DLeftWall(); draw3DRightWall(); drawLogoOnWall(1.42f,1.15f); drawLogoOnWall(13.71f,1.15f); drawRungs3D();
    drawFenceWing(false); drawFenceWing(true); drawSpecificWalkway(false); drawSpecificWalkway(true);
    drawLEDScreen(); 
    drawDynamicElements();
    glutSwapBuffers();
}

void reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45.0f, (float)w/h, 1.0f, 2000.0f); glMatrixMode(GL_MODELVIEW); }
void init() { glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); glEnable(GL_COLOR_MATERIAL); glEnable(GL_NORMALIZE); glClearColor(COL_SKY.r, COL_SKY.g, COL_SKY.b, 1.0f); }

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_W, WINDOW_H); glutCreateWindow("ashenafi_deresa || ASTU 3D GEDA GATE Simulation");
    init(); glutDisplayFunc(display); glutReshapeFunc(reshape); glutIdleFunc(idle); glutKeyboardFunc(keyboard);
    glutMainLoop(); return 0;
}
