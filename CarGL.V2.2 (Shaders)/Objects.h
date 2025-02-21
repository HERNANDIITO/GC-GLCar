
/***************************************************************************************

    CarGL (Objects.h)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  --------------------------------------------------------------------------------------

    2012 - 2022 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

****************************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#define GLEW_STATIC

#include "Shader.h"
#include "Program.h"

#include <GL/glui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Identificadores internos de los objetos y el coche
#define CARRETERA_ID    10
#define EDIFICIO_ID     20
#define GARAGE_ID       30
#define WHEAT_ID        40
#define FENCE_ID        50
#define LIGHTPOST_ID    70
#define ROCK1_ID        60
#define ROCK2_ID        65
#define TREE_ID         80
#define MOUNTAIN1_ID    90
#define MOUNTAIN2_ID    95
#define LOG1_ID         100
#define LOG2_ID         105
#define GRASS_ID        110
#define BUSH_ID         120
#define COCHE_ID	    500

// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT0_POSITION_ID   210
#define LIGHT0_INTENSITY_ID  220
#define LIGHT0_AMBIENT_ID    230
#define LIGHT0_DIFFUSE_ID    240
#define LIGHT0_SPECULAR_ID   250

#define LIGHT1_ENABLED_ID    201
#define LIGHT1_POSITION_ID   211
#define LIGHT1_INTENSITY_ID  221
#define LIGHT1_AMBIENT_ID    231
#define LIGHT1_DIFFUSE_ID    241
#define LIGHT1_SPECULAR_ID   251

#define LIGHT2_ENABLED_ID    202
#define LIGHT2_POSITION_ID   212
#define LIGHT2_INTENSITY_ID  222
#define LIGHT2_AMBIENT_ID    232
#define LIGHT2_DIFFUSE_ID    242
#define LIGHT2_SPECULAR_ID   252

#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define SEL_ID               500
#define CAM_ID               501
#define PROY_ID              502
#define FACES_ID             503
#define VISUALIZATION_ID     504
#define CULLING_ID           505
#define Z_BUFFER_ID          506

// Datos del formato 3DS (x, y, z, A, B, C, u, v)
#define POSITION_COMPONENT_COUNT    3
#define NORMAL_COMPONENT_COUNT      3
#define UV_COMPONENT_COUNT          2
// C�lculo del stride (3+3+2)*4 = 8*4 = 32
#define STRIDE                      32

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"

//************************************************************** Clase TPrimtiva

class TPrimitiva
{
public: // Atributos de la clase
		int ID;				    // DisplayLists del objeto
		int tipo;               // Tipo de Objeto
		float tx,ty,tz; 	    // Posici�n del objeto
		float sx,sy,sz; 	    // Escalado del objeto
		float rx,ry,rz;     	// Rotaci�n del objeto
		float rr;               // Rotaci�n de las ruedas
        float gr;               // Giro de las ruedas
        float gc;               // Giro del coche
		float colores[2][4];    // Color RGB y canal Alfa

		float   *modelo0;        // modelo a representar
		int     num_vertices0;   // n�mero de v�rtices

        float   *modelo1;        // modelo a representar
		int     num_vertices1;   // n�mero de v�rtices

public: // M�todos
 		TPrimitiva(int DL, int tipo);
        void __fastcall Render(int seleccion, bool reflejo=false);
};

//************************************************************** Clase TEscena

class TEscena
{
public: // Atributos de la clase
		int   	seleccion;   	// Objeto seleccionado, 0=ninguno
        int     camara;
        int     proyeccion;
        int		num_objects;    // N�mero de objetos (excepto coches)
        int     num_cars;       // N�mero de coches

        TPrimitiva  *cars[10];
        TPrimitiva  *objects[100];

        // Handles de los attributes y uniforms
        int aPositionLocation;
        int aNormalLocation;
        
        int uProjectionMatrixLocation;
        int uMVMatrixLocation;
		int uVMatrixLocation;
		int uColorLocation;

		int uLuz0Location;
		int uLuz0Ambient;
		int uLuz0Diffuse;
		int uLuz0Specular;
		int uLuz0Position;
		int uLuz0Intensity;

		int uLuz1Location;
		int uLuz1Ambient;
		int uLuz1Diffuse;
		int uLuz1Specular;
		int uLuz1Position;
		int uLuz1Intensity;

		int uLuz2Location;
		int uLuz2Ambient;
		int uLuz2Diffuse;
		int uLuz2Specular;
		int uLuz2Position;
		int uLuz2Intensity;

        bool changeProy;

		glm::mat4 projectionMatrix; // Almacena la matriz de proyecci�n
        glm::mat4 viewMatrix;       // Almacena la matriz de la vista (c�mara)

		Program  *shaderProgram;    // Almacena el programa de OpenGL (ShaderProgram)

        // Vectores de luces y materiales
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4];

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat light2_ambient[4];
        GLfloat light2_diffuse[4];
        GLfloat light2_specular[4];
        GLfloat light2_position[4];

        GLfloat mat_ambient[4];
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat mat_shininess[1];

        float   xy_aspect;
        int     last_x, last_y;

        // live variables usadas por GLUI en TGui
        int     wireframe;
        int     z_buffer;
        int     culling;

        int     show_car;
        int     show_wheels;
        int     show_road;

        GLfloat yaw;
        GLfloat pitch;
        GLfloat cameraDistance = 10.0f;
        GLfloat sensibility = 0.05f;

        GLfloat camX = cameraDistance;
        GLfloat camY = cameraDistance;
        GLfloat camZ = cameraDistance;

        GLfloat targetX = 0.0f;
        GLfloat targetY = 0.0f;
        GLfloat targetZ = 0.0f;

        bool isCtrlPressed      = false;
        bool isShiftPressed     = false;
        bool leftButtonPressed  = false;
        bool rightButtonPressed = false;

        GLfloat view_position[3];
        GLfloat view_rotate[16];
        float   scale;



public: // M�todos
		TEscena();

        void __fastcall InitGL();
		void __fastcall Render();
		void __fastcall RenderCars(bool reflejo=false);
		void __fastcall RenderObjects(bool reflejo=false);

		void __fastcall AddCar(TPrimitiva *car);
		void __fastcall AddObject(TPrimitiva *object);
        void __fastcall CrearEscenario();

		TPrimitiva __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);


};

//************************************************************** Clase TGui

class TGui
{
public:
        int             window_id;

        // live variables usadas por GLUI
        int             sel;
        int             cam;
        int             xIni;
        int             yIni;
        int             proy;
        int             faces;
        int             visualization;
        int             enable_panel2;

        int             light0_enabled;
        float           light0_intensity;
        float           light0_position[4];

        int             light1_enabled;
        float           light1_intensity;
        float           light1_position[4];

        int             light2_enabled;
        float           light2_intensity;
        float           light2_position[4];

        bool            pressingCtrl;

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_Spinner    *light2_spinner;
        GLUI_RadioGroup *radio;
        GLUI_Panel      *obj_panel;
        GLUI_Rotation   *view_rot;

public:
        TGui();
        void __fastcall Init(int main_window);
        void __fastcall ControlCallback(int control);
        void __fastcall Idle( void );
        void __fastcall Reshape( int x, int y  );
        void __fastcall Motion( int x, int y  );
        void __fastcall Mouse(int button, int button_state, int x, int y );
};

//************************************************************** Variables de clase

extern TEscena  escena;
extern TGui     gui;

#endif
