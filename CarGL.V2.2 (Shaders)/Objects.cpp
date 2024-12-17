
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    2012 - 2022 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera

//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

// metodo para girar la rueda y el coche


TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/road.3ds", &num_vertices0);
            break;
		}
		case EDIFICIO_ID: {  // Creaci�n del edificio
		    tz = ty = 0;
            tx = -27;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/house.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
        case GARAGE_ID: {  // Creaci�n del garaje
		    tz = ty = 0;
            tx = -27;
            rx = 270;
            ry = 90;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/garage.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
        case WHEAT_ID: {  // Creaci�n del trigo
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 1;
            colores[0][1] = 0.85;
            colores[0][2] = 0.45;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/wheat.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
        case GRASS_ID: {  // Creaci�n del trigo
		    ty = -0.1;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.45;
            colores[0][1] = 0.70;
            colores[0][2] = 0.14;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/grass.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
        case FENCE_ID: {  // Creaci�n de la valla
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 1;
            colores[0][1] = 1;
            colores[0][2] = 1;
            colores[0][3] = 1;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/fence.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case ROCK1_ID: {  // Creaci�n de la roca1
		    tz = ty = 0;
            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.53;
            colores[0][1] = 0.51;
            colores[0][2] = 0.52;


            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/rock1.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case ROCK2_ID: {  // Creaci�n de la roca2
		    ty = 0.25;
            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.53;
            colores[0][1] = 0.51;
            colores[0][2] = 0.52;


            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/rock2.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case TREE_ID: {  // Creaci�n de la valla
		    tz = ty = 0;
            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.13;
            colores[0][1] = 0.40;
            colores[0][2] = 0.18;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/tree.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case LIGHTPOST_ID: {  // Creaci�n de la valla
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.40;
            colores[0][1] = 0.26;
            colores[0][2] = 0.15;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/lightpost.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case MOUNTAIN1_ID: {  // Creaci�n de la montaña1
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.53;
            colores[0][1] = 0.51;
            colores[0][2] = 0.52;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/mountain1.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case MOUNTAIN2_ID: {  // Creaci�n de la montaña2
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.53;
            colores[0][1] = 0.51;
            colores[0][2] = 0.52;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/mountain2.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case LOG1_ID: {  // Creaci�n de la montaña2
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.25;
            colores[0][1] = 0.15;
            colores[0][2] = 0.08;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/log1.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case LOG2_ID: {  // Creaci�n de la montaña2
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.25;
            colores[0][1] = 0.15;
            colores[0][2] = 0.08;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/log2.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case BUSH_ID: {  // Creaci�n de la arbusto
		    tz = ty = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            colores[0][0] = 0.13;
            colores[0][1] = 0.40;
            colores[0][2] = 0.18;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/pablo/bush.3ds", &num_vertices0);
            modelo1 = NULL;
            break;
		}
		case COCHE_ID: { // Creaci�n del coche

		    tx = -2.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;
            gc = 0.0;
            gr = 0.0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            colores[0][0] = 0.5f;
            colores[0][1] = 0.5f;
            colores[0][2] = 0.5f;
            colores[0][3] = 1.0f;

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../modelos/Pablo/car.3ds", &num_vertices0);
            modelo1 = Load3DS("../../modelos/Pablo/wheels.3ds", &num_vertices1);
            break;
		}
	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (tipo) {
        case CARRETERA_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

                // Pintar las l�neas
                glUniform4fv(escena.uColorLocation, 1, colores[1]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);


            }
            break;
        } // case CARRETERA_ID:
        case EDIFICIO_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        } // case CARRETERA_ID:
        case GARAGE_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case WHEAT_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case GRASS_ID: {
            if (escena.show_road) {
                tz = tx = 0;
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case FENCE_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case TREE_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ROCK1_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ROCK2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case LIGHTPOST_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case MOUNTAIN1_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case MOUNTAIN2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case LOG1_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case LOG2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case BUSH_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case COCHE_ID: {
            
            if (escena.show_car) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rx), glm::vec3(1,0,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }


            if (escena.show_wheels)
            {
                float radGC = glm::radians(gc);

                float det = 2.42;
                float de  = 0.95;

                // Centro coche
                float cex = -det * sin(radGC);
                float cez = -det * cos(radGC);

                // Rueda delantera izquierda
                float dix = tx + de * cos(radGC);
                float diz = tz - de * sin(radGC);

                // Rueda delantera derecha
                float ddx = tx - de * cos(radGC);
                float ddz = tz + de * sin(radGC);

                // Rueda trasera izquierda
                float tix = tx + cex + de * cos(radGC);
                float tiz = tz + cez - de * sin(radGC);

                // Rueda trasera derecha
                float tdx = tx + cex - de * cos(radGC);
                float tdz = tz + cez + de * sin(radGC);

                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA Delantera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(dix, ty+0.30, diz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc + gr), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Derecha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(ddx, ty+0.30, ddz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc + gr), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tix, ty+0.30, tiz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tdx, ty+0.30, tdz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

            }
            break;
        };
    }
}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 100.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3  * sizeof(float));
    memcpy(view_rotate,   view_rotate_c,   16 * sizeof(float));

    memcpy(light0_ambient,  light0_ambient_c,  4*sizeof(float));
    memcpy(light0_diffuse,  light0_diffuse_c,  4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient,  light1_ambient_c,  4*sizeof(float));
    memcpy(light1_diffuse,  light1_diffuse_c,  4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient,  light2_ambient_c,  4*sizeof(float));
    memcpy(light2_diffuse,  light2_diffuse_c,  4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient,   mat_ambient_c,   4*sizeof(float));
    memcpy(mat_diffuse,   mat_diffuse_c,   4*sizeof(float));
    memcpy(mat_specular,  mat_specular_c,  4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glCullFace(GL_BACK);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Inicializaci�n de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));

    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);

    uLuz0Location   = shaderProgram->uniform("uLuz0Location");
    uLuz0Ambient    = shaderProgram->uniform("uLuz0Ambient");
    uLuz0Diffuse    = shaderProgram->uniform("uLuz0Diffuse");
    uLuz0Specular   = shaderProgram->uniform("uLuz0Specular");
    uLuz0Position   = shaderProgram->uniform("uLuz0Position");
    uLuz0Intensity  = shaderProgram->uniform("uLuz0Intensity");

    uLuz1Location   = shaderProgram->uniform("uLuz1Location");
    uLuz1Ambient    = shaderProgram->uniform("uLuz1Ambient");
    uLuz1Diffuse    = shaderProgram->uniform("uLuz1Diffuse");
    uLuz1Specular   = shaderProgram->uniform("uLuz1Specular");
    uLuz1Position   = shaderProgram->uniform("uLuz1Position");
    uLuz1Intensity  = shaderProgram->uniform("uLuz1Intensity");

    uLuz2Location   = shaderProgram->uniform("uLuz2Location");
    uLuz2Ambient    = shaderProgram->uniform("uLuz2Ambient");
    uLuz2Diffuse    = shaderProgram->uniform("uLuz2Diffuse");
    uLuz2Specular   = shaderProgram->uniform("uLuz2Specular");
    uLuz2Position   = shaderProgram->uniform("uLuz2Position");
    uLuz2Intensity  = shaderProgram->uniform("uLuz2Intensity");

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyecci�n perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscen    garage->rx=180;a::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        glStencilFunc(GL_ALWAYS, i+1, 0xFF);
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    switch (camara) {
        case 0: {
            // CAMARA POR DEFECTO
            viewMatrix      = glm::mat4(1.0f);
            rotateMatrix    = glm::make_mat4(view_rotate);
            viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
            viewMatrix      = viewMatrix * rotateMatrix;
            viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale/100.0, scale/100.0, scale/100.0));
            break;
        }

        case 1: {
            // CAMARA AEREA
            TPrimitiva* selectedCar = escena.GetCar(seleccion);

            glm::vec3 eye       = glm::vec3(selectedCar->tx, 25.0f, selectedCar->tz);
            glm::vec3 center    = glm::vec3(selectedCar->tx, 0.0f, selectedCar->tz);
            glm::vec3 up        = glm::vec3(0.0f, 0.0f, 1.0f);

            viewMatrix = glm::lookAt(eye, center, up);

            break;

        }

        case 2: {
            // CAMARA DE SEGUIMIENTO

            TPrimitiva* selectedCar = escena.GetCar(seleccion);
            float angleInRadians = glm::radians(selectedCar->gc + selectedCar->rx);
            glm::vec3 cameraOffset = glm::vec3(0.00f, 3.5f, -7.5f);

            glm::mat4 rotationMatrix = glm::rotate(
                glm::mat4(1.0f),
                angleInRadians,
                glm::vec3(0.0f, 1.0f, 0.0f)
            );     

            cameraOffset = glm::vec3(rotationMatrix * glm::vec4(cameraOffset, 1.0f));    

            glm::vec3 eye       = glm::vec3(selectedCar->tx, selectedCar->ty, selectedCar->tz) + cameraOffset;
            glm::vec3 center    = glm::vec3(selectedCar->tx, selectedCar->ty, selectedCar->tz);
            glm::vec3 up        = glm::vec3(0.0f, 1.0f, 0.0f);

            viewMatrix = glm::lookAt(eye, center, up);
            break;

        }

        case 3: {
            // CAMARA LIBRE

            glm::vec3 cameraPos = glm::vec3(camX, camY, camZ);
            glm::vec3 target = glm::vec3(targetX, targetY, targetZ); // Centro de la escena
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);     // Arriba en el mundo

            viewMatrix = glm::lookAt(cameraPos, target, up);
        }
        default: {
            break;
        }
    }

    if ( changeProy ) {
        changeProy = false;
        int x, y, ancho, alto;
        GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
        glViewport( x, y, ancho, alto );

        if (alto == 0) alto = 1;
        // !!!!! ATENCI�N: comprobar que alto no sea 0, sino divisi�n por 0 !!!!!!
        escena.xy_aspect = (float)ancho / (float)alto;

        switch (proyeccion) {
            case 0:
                std::cout << "Proyeccion paralela seleccionada... \n";
                escena.projectionMatrix = glm::ortho(
                    -10.0f, 10.0f,
                    -10.0f / escena.xy_aspect, 10.0f / escena.xy_aspect,
                    0.1f, 100.0f
                );
                break;

            case 1:
                std::cout << "Proyeccion paralela perspectiva...  \n";
                escena.projectionMatrix = glm::perspective(
                    45.0f,
                    escena.xy_aspect,
                    0.1f,
                    1000.0f
                );
                break;
            
            default:
                break;
        }

        glUseProgram(escena.shaderProgram->ReturnProgramID());
        glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

        //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

        glutPostRedisplay();
    }

    // Luz 0

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1f(uLuz0Intensity, gui.light0_intensity);
    glUniform4fv(uLuz0Ambient,  1, (const GLfloat *) escena.light0_ambient);
    glUniform4fv(uLuz0Diffuse,  1, (const GLfloat *) escena.light0_diffuse);
    glUniform4fv(uLuz0Specular, 1, (const GLfloat *) escena.light0_specular);
    glUniform4fv(uLuz0Position, 1, (const GLfloat *) escena.light0_position);

    // Luz 1

    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1f(uLuz1Intensity, gui.light1_intensity);
    glUniform4fv(uLuz1Ambient,  1, (const GLfloat *) escena.light1_ambient);
    glUniform4fv(uLuz1Diffuse,  1, (const GLfloat *) escena.light1_diffuse);
    glUniform4fv(uLuz1Specular, 1, (const GLfloat *) escena.light1_specular);
    glUniform4fv(uLuz1Position, 1, (const GLfloat *) escena.light1_position);

    // Luz 2

    glUniform1f(uLuz2Intensity, gui.light2_intensity);
    glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniform4fv(uLuz2Ambient,  1, (const GLfloat *) escena.light2_ambient);
    glUniform4fv(uLuz2Diffuse,  1, (const GLfloat *) escena.light2_diffuse);
    glUniform4fv(uLuz2Specular, 1, (const GLfloat *) escena.light2_specular);
    glUniform4fv(uLuz2Position, 1, (const GLfloat *) escena.light2_position);

    // Matrix

    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a trav�s del rat�n
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    int h, index;
    GLint viewport[4];
    
    index = -1;
    glGetIntegerv(GL_VIEWPORT, viewport);
    h = viewport[3];

    glReadPixels(mouse_x, h-mouse_y+81, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    std::cout << "Coche seleccionado: ";
    std::cout << index;
    std::cout << "\n";

    if ( index > 0 ) {
        // Hacemos gris el coche seleccionado previamente
        TPrimitiva* selectedCar = GetCar(seleccion);
        selectedCar->colores[0][0] = 0.5f;
        selectedCar->colores[0][1] = 0.5f;
        selectedCar->colores[0][2] = 0.5f;
        selectedCar->colores[0][3] = 1.0f;

        seleccion = index;
        gui.sel = index;

        // Ponemos bonito el coche recien seleccionado
        selectedCar = GetCar(seleccion);
        selectedCar->colores[0][0] = 0.7f;
        selectedCar->colores[0][1] = 1.0f;
        selectedCar->colores[0][2] = 0.1f;
        selectedCar->colores[0][3] = 1.0f;
    }

    gui.glui->sync_live();
}

// Crea todo el escenario
void __fastcall TEscena::CrearEscenario()
{
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);

    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);

    car2->colores[0][0] = 0.5;
    car2->colores[0][1] = 0.5;
    car2->colores[0][2] = 0.5;
    car2->colores[0][3] = 1.0;
    car2->tx = 2;
    car2->tz = 3;

    TPrimitiva *edificio2 = new TPrimitiva(EDIFICIO_ID, EDIFICIO_ID);

    edificio2->tx=8;
    edificio2->ry=270;
    edificio2->colores[0][2]=0.8;

    TPrimitiva *garage = new TPrimitiva(GARAGE_ID, GARAGE_ID);

    garage->tx=10;
    garage->tz=7;
    garage->ty=0;
    garage->colores[0][2]=0.8;

    TPrimitiva *wheat1 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat1->tx = 7;
    wheat1->ty = 0;
    wheat1->tz = -4;

    TPrimitiva *wheat2 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat2->tx = 7;
    wheat2->ty = 0;
    wheat2->tz = -6;

    TPrimitiva *wheat3 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat3->tx = 7;
    wheat3->ty = 0;
    wheat3->tz = -8;

    TPrimitiva *wheat4 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat4->tx = 7;
    wheat4->ty = 0;
    wheat4->tz = -10;

    TPrimitiva *wheat5 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat5->tx = 7;
    wheat5->ty = 0;
    wheat5->tz = -11;

    TPrimitiva *wheat6 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat6->tx = 9.25;
    wheat6->ty = 0;
    wheat6->tz = -4;

    TPrimitiva *wheat7 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat7->tx = 9.25;
    wheat7->ty = 0;
    wheat7->tz = -6;

    TPrimitiva *wheat8 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat8->tx = 9.25;
    wheat8->ty = 0;
    wheat8->tz = -8;

    TPrimitiva *wheat9 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat9->tx = 9.25;
    wheat9->ty = 0;
    wheat9->tz = -10;

    TPrimitiva *wheat10 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat10->tx = 9.25;
    wheat10->ty = 0;
    wheat10->tz = -11;

    TPrimitiva *wheat11 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat11->tx = 11.5;
    wheat11->ty = 0;
    wheat11->tz = -4;

    TPrimitiva *wheat12 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat12->tx = 11.5;
    wheat12->ty = 0;
    wheat12->tz = -6;

    TPrimitiva *wheat13 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat13->tx = 11.5;
    wheat13->ty = 0;
    wheat13->tz = -8;

    TPrimitiva *wheat14 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat14->tx = 11.5;
    wheat14->ty = 0;
    wheat14->tz = -10;

    TPrimitiva *wheat15 = new TPrimitiva(WHEAT_ID, WHEAT_ID);

    wheat15->tx = 11.5;
    wheat15->ty = 0;
    wheat15->tz = -11;

    TPrimitiva *fence1 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence1->tx = 5.75;
    fence1->ty = 0;
    fence1->tz = -4.25;
    fence1->ry = 90;

    TPrimitiva *fence2 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence2->tx = 5.75;
    fence2->ty = 0;
    fence2->tz = -7.75;
    fence2->ry = 90;

    TPrimitiva *fence3 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence3->tx = 5.75;
    fence3->ty = 0;
    fence3->tz = -11;
    fence3->ry = 90;

    TPrimitiva *fence4 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence4->tx = 7.25+(3.5*0);
    fence4->ty = 0;
    fence4->tz = -12.5;
    fence4->ry = 180;

    TPrimitiva *fence5 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence5->tx = 7.25+(3.5*1);
    fence5->ty = 0;
    fence5->tz = -12.5;
    fence5->ry = 180;

    TPrimitiva *fence6 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence6->tx = 5.75+(3.5*2);
    fence6->ty = 0;
    fence6->tz = -4.25;
    fence6->ry = 90;

    TPrimitiva *fence7 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence7->tx = 5.75+(3.5*2);
    fence7->ty = 0;
    fence7->tz = -7.75;
    fence7->ry = 90;

    TPrimitiva *fence8 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence8->tx = 5.75+(3.5*2);
    fence8->ty = 0;
    fence8->tz = -11;
    fence8->ry = 90;

    TPrimitiva *fence9 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence9->tx = 7.25+3.5;
    fence9->ty = 0;
    fence9->tz = -2.5;
    fence9->ry = 180;

    TPrimitiva *fence10 = new TPrimitiva(FENCE_ID, FENCE_ID);

    fence10->tx = 7.25;
    fence10->ty = 0;
    fence10->tz = -2.5;
    fence10->ry = 180;

    TPrimitiva *rock1 = new TPrimitiva(ROCK1_ID, ROCK1_ID);

    rock1->tx = -7;
    rock1->tz = 2.5;

    TPrimitiva *rock2 = new TPrimitiva(ROCK2_ID, ROCK2_ID);

    rock2->tx = -6;
    rock2->tz = 3;
    rock2->rx = 45;

    TPrimitiva *tree = new TPrimitiva(TREE_ID, TREE_ID);

    tree->tx = -5.5;
    tree->tz = 2;

    TPrimitiva *lightpost_drch_1 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_drch_1->tx = -6.5;
    lightpost_drch_1->tz = -6;
    lightpost_drch_1->ry = 90;

    TPrimitiva *lightpost_izq_1 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_izq_1->tx = 5;
    lightpost_izq_1->tz = -3;
    lightpost_izq_1->ry = -90;

    TPrimitiva *lightpost_drch_2 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_drch_2->tx = -6.5;
    lightpost_drch_2->tz = -6+(12*1);
    lightpost_drch_2->ry = 90;

    TPrimitiva *lightpost_izq_2 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_izq_2->tx = 5;
    lightpost_izq_2->tz = -3+(12*1);
    lightpost_izq_2->ry = -90;

    TPrimitiva *lightpost_drch_3 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_drch_3->tx = -6.5;
    lightpost_drch_3->tz = -6+(12*2);
    lightpost_drch_3->ry = 90;

    TPrimitiva *lightpost_izq_3 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_izq_3->tx = 5;
    lightpost_izq_3->tz = -3+(12*2);
    lightpost_izq_3->ry = -90;

    TPrimitiva *lightpost_drch_4 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_drch_4->tx = -6.5;
    lightpost_drch_4->tz = -6+(12*3);
    lightpost_drch_4->ry = 90;

    TPrimitiva *lightpost_izq_4 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_izq_4->tx = 5;
    lightpost_izq_4->tz = -3+(12*3);
    lightpost_izq_4->ry = -90;

    TPrimitiva *lightpost_drch_5 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_drch_5->tx = -6.5;
    lightpost_drch_5->tz = -6+(12*4);
    lightpost_drch_5->ry = 90;

    TPrimitiva *lightpost_izq_5 = new TPrimitiva(LIGHTPOST_ID, LIGHTPOST_ID);

    lightpost_izq_5->tx = 5;
    lightpost_izq_5->tz = -3+(12*4);
    lightpost_izq_5->ry = -90;

    TPrimitiva *mountain1 = new TPrimitiva(MOUNTAIN1_ID, MOUNTAIN1_ID);

    mountain1->tx = 25;
    mountain1->tz = 0;

    TPrimitiva *mountain2 = new TPrimitiva(MOUNTAIN2_ID, MOUNTAIN2_ID);

    mountain2->tx = 30;
    mountain2->tz = 10;

    TPrimitiva *mountain3 = new TPrimitiva(MOUNTAIN2_ID, MOUNTAIN2_ID);

    mountain3->tx = 45;
    mountain3->tz = 30;
    mountain3->ry = 47;


    TPrimitiva *tree2 = new TPrimitiva(TREE_ID, TREE_ID);

    tree2->tx = 24;
    tree2->tz = 11;

    TPrimitiva *tree3 = new TPrimitiva(TREE_ID, TREE_ID);

    tree3->tx = 20;
    tree3->tz = 8;

    TPrimitiva *tree4 = new TPrimitiva(TREE_ID, TREE_ID);

    tree4->tx = 20;
    tree4->tz = 18;

    TPrimitiva *tree5 = new TPrimitiva(TREE_ID, TREE_ID);

    tree5->tx = 15;
    tree5->tz = 12.5;

    TPrimitiva *rock3 = new TPrimitiva(ROCK1_ID, ROCK1_ID);

    rock3->tx = 21;
    rock3->tz = 8.5;

    TPrimitiva *rock4 = new TPrimitiva(ROCK2_ID, ROCK2_ID);

    rock4->tx = 22;
    rock4->tz = 9;
    rock4->rx = 45;

    TPrimitiva *rock6 = new TPrimitiva(ROCK1_ID, ROCK1_ID);

    rock6->tx = 15.6;
    rock6->tz = 13.25;
    rock6->ry = 76;

    TPrimitiva *rock5 = new TPrimitiva(ROCK2_ID, ROCK2_ID);

    rock5->tx = 20.75;
    rock5->tz = 18.75;
    rock5->rx = 45;

    TPrimitiva *log1 = new TPrimitiva(LOG1_ID, LOG1_ID);

    log1->tx = 22.75;
    log1->tz = 24.75;
    log1->ry = 23;

    TPrimitiva *log2 = new TPrimitiva(LOG2_ID, LOG2_ID);

    log2->tx = 23.75;
    log2->tz = 35.75;
    log2->ry = 55;

    TPrimitiva *grass = new TPrimitiva(GRASS_ID, GRASS_ID);
    grass->ty = -0.30;

    TPrimitiva *bush1 = new TPrimitiva(BUSH_ID, BUSH_ID);
    bush1->tx = 15;
    bush1->tz = 17;
    bush1->ry = 30;

    TPrimitiva *bush2 = new TPrimitiva(BUSH_ID, BUSH_ID);
    bush2->tx = 16;
    bush2->tz = 30;
    bush2->ry = 45;

    TPrimitiva *bush3 = new TPrimitiva(BUSH_ID, BUSH_ID);
    bush3->tx = 27;
    bush3->tz = 28;
    bush3->ry = 0;

    // A�adir objetos
    AddObject(road);

    AddObject(edificio2);

    AddObject(garage);

    AddObject(wheat1);
    AddObject(wheat2);
    AddObject(wheat3);
    AddObject(wheat4);
    AddObject(wheat5);

    AddObject(wheat6);
    AddObject(wheat7);
    AddObject(wheat8);
    AddObject(wheat9);
    AddObject(wheat10);

    AddObject(wheat11);
    AddObject(wheat12);
    AddObject(wheat13);
    AddObject(wheat14);
    AddObject(wheat15);

    AddObject(fence1);
    AddObject(fence2);
    AddObject(fence3);
    AddObject(fence4);

    AddObject(fence5);
    AddObject(fence6);

    AddObject(fence7);
    AddObject(fence8);
    AddObject(fence9);
    AddObject(fence10);

    AddObject(rock1);
    AddObject(rock2);

    AddObject(rock3);
    AddObject(rock4);
    AddObject(rock5);
    AddObject(rock6);

    AddObject(tree);
    AddObject(tree2);
    AddObject(tree3);
    AddObject(tree4);
    AddObject(tree5);

    AddObject(log1);
    AddObject(log2);

    AddObject(lightpost_drch_1);
    AddObject(lightpost_izq_1);
    AddObject(lightpost_drch_2);
    AddObject(lightpost_izq_2);
    AddObject(lightpost_drch_3);
    AddObject(lightpost_izq_3);
    AddObject(lightpost_drch_4);
    AddObject(lightpost_izq_4);
    AddObject(lightpost_drch_5);

    AddObject(mountain1);
    AddObject(mountain2);
    AddObject(mountain3);

    AddObject(grass);

    AddObject(bush1);
    AddObject(bush2);
    AddObject(bush3);

    // A�adir coches
    AddCar(car1);
    AddCar(car2);
}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 0;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Opciones nuevas", false );

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panelSeleccion = new GLUI_Panel(obj_panel, "Seleccion");

    GLUI_RadioGroup *radioGroupSeleccion = new GLUI_RadioGroup(panelSeleccion, &sel, SEL_ID, controlCallback);

    glui->add_radiobutton_to_group(radioGroupSeleccion, "NINGUNO");
    glui->add_radiobutton_to_group(radioGroupSeleccion, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroupSeleccion, "COCHE 2");

    // A�ade un panel con texto con el valor de la camara
    GLUI_Panel *panelCamara = new GLUI_Panel(obj_panel, "Camara");

    GLUI_RadioGroup *radioGroupCamara = new GLUI_RadioGroup(panelCamara, &cam, CAM_ID, controlCallback);

    glui->add_radiobutton_to_group(radioGroupCamara, "POR DEFECTO");
    glui->add_radiobutton_to_group(radioGroupCamara, "AEREA");
    glui->add_radiobutton_to_group(radioGroupCamara, "SEGUIMIENTO");
    glui->add_radiobutton_to_group(radioGroupCamara, "LIBRE");

    // A�ade un panel con texto con el valor de la proyeccion
    GLUI_Panel *panelProyeccion = new GLUI_Panel(obj_panel, "Proyeccion");

    GLUI_RadioGroup *radioGroupProyeccion = new GLUI_RadioGroup(panelProyeccion, &proy, PROY_ID, controlCallback);

    glui->add_radiobutton_to_group(radioGroupProyeccion, "PARALELA");
    glui->add_radiobutton_to_group(radioGroupProyeccion, "PERSPECTIVA");

    // A�ade un panel con texto con el valor de las caras interiores o exteriores
    GLUI_Panel *panelNormals = new GLUI_Panel(obj_panel, "Cara exterior");

    GLUI_RadioGroup *radioGroupNormals = new GLUI_RadioGroup(panelNormals, &faces, FACES_ID, controlCallback);

    glui->add_radiobutton_to_group(radioGroupNormals, "HORARIO");
    glui->add_radiobutton_to_group(radioGroupNormals, "ANTIHORARIO");

    // A�ade un panel con texto con el valor de las caras interiores o exteriores
    GLUI_Panel *panelVisualizacion = new GLUI_Panel(obj_panel, "Visualizacion");

    GLUI_RadioGroup *radioGroupVisualizacion = new GLUI_RadioGroup(panelVisualizacion, &visualization, VISUALIZATION_ID, controlCallback);

    glui->add_radiobutton_to_group(radioGroupVisualizacion, "SOLIDO");
    glui->add_radiobutton_to_group(radioGroupVisualizacion, "ALAMBRICO");
    glui->add_radiobutton_to_group(radioGroupVisualizacion, "PUNTOS");

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, CULLING_ID, controlCallback );
    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, Z_BUFFER_ID, controlCallback );

    /******** A�ade controles para las luces ********/

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", true );

    GLUI_Rollout *light0 = new GLUI_Rollout(roll_lights, "Luz 0", false );
    GLUI_Rollout *light1 = new GLUI_Rollout(roll_lights, "Luz 1", false );
    GLUI_Rollout *light2 = new GLUI_Rollout(roll_lights, "Luz 2", false );

    // LUZ 0

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;

    new GLUI_StaticText(light0, "Posicion X:");
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light0, "Posicion Y:");
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light0, "Posicion Z:");
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light0, "Ambiente:");
    sb = new GLUI_Scrollbar( light0, "Ambiente",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_ambient[0], LIGHT0_AMBIENT_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light0, "Difusa:");
    sb = new GLUI_Scrollbar( light0, "Difusa",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_diffuse[0],LIGHT0_DIFFUSE_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light0, "Especular:");
    sb = new GLUI_Scrollbar( light0, "Especular",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_specular[0],LIGHT0_SPECULAR_ID,controlCallback);
    sb->set_float_limits(0,1);

    // LUZ 1

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );

    new GLUI_StaticText(light1, "Posicion X:");
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light1, "Posicion Y:");
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light1, "Posicion Z:");
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light1, "Ambiente:");
    sb = new GLUI_Scrollbar( light1, "Ambiente",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_ambient[0], LIGHT1_AMBIENT_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light1, "Difusa:");
    sb = new GLUI_Scrollbar( light1, "Difusa",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_diffuse[0],LIGHT1_DIFFUSE_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light1, "Especular:");
    sb = new GLUI_Scrollbar( light1, "Especular",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_specular[0],LIGHT1_SPECULAR_ID,controlCallback);
    sb->set_float_limits(0,1);

    // LUZ 2

    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );

    new GLUI_StaticText(light2, "Posicion X:");
    sb = new GLUI_Scrollbar( light2, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[0],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light2, "Posicion Y:");
    sb = new GLUI_Scrollbar( light2, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[1],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light2, "Posicion Z:");
    sb = new GLUI_Scrollbar( light2, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[2],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText(light2, "Ambiente:");
    sb = new GLUI_Scrollbar( light2, "Ambiente",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_ambient[0], LIGHT2_AMBIENT_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light2, "Difusa:");
    sb = new GLUI_Scrollbar( light2, "Difusa",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_diffuse[0],LIGHT2_DIFFUSE_ID,controlCallback);
    sb->set_float_limits(0,1);

    new GLUI_StaticText(light2, "Especular:");
    sb = new GLUI_Scrollbar( light2, "Especular",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_specular[0],LIGHT2_SPECULAR_ID,controlCallback);
    sb->set_float_limits(0,1);

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", false );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );


    /*** Disable/Enable botones ***/
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Permitir Movimiento", &enable_panel2 );
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2012-2022 (C) Juan Antonio Puchol  " );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {
            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT0_AMBIENT_ID: {
            escena.light0_ambient[1] = escena.light0_ambient[0]; 
            escena.light0_ambient[2] = escena.light0_ambient[0]; 
            escena.light0_ambient[3] = 1.0f;
            break;
        }
        case LIGHT0_DIFFUSE_ID: {
            escena.light0_diffuse[1] = escena.light0_diffuse[0]; 
            escena.light0_diffuse[2] = escena.light0_diffuse[0]; 
            escena.light0_diffuse[3] = 1.0f;
            break;
        }
        case LIGHT0_SPECULAR_ID: {
            escena.light0_specular[1] = escena.light0_specular[0]; 
            escena.light0_specular[2] = escena.light0_specular[0]; 
            escena.light0_specular[3] = 1.0f;
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT1_INTENSITY_ID: {
            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case LIGHT1_AMBIENT_ID: {
            escena.light1_ambient[1] = escena.light1_ambient[0]; 
            escena.light1_ambient[2] = escena.light1_ambient[0]; 
            break;
        }
        case LIGHT1_DIFFUSE_ID: {
            escena.light1_diffuse[1] = escena.light1_diffuse[0]; 
            escena.light1_diffuse[2] = escena.light1_diffuse[0]; 
            break;
        }
        case LIGHT1_SPECULAR_ID: {
            escena.light1_specular[1] = escena.light1_specular[0]; 
            escena.light1_specular[2] = escena.light1_specular[0]; 
            break;
        }
        case LIGHT2_ENABLED_ID: {
            if ( light2_enabled )
                light2_spinner->enable();
            else
                light2_spinner->disable();
            break;
        }
        case LIGHT2_INTENSITY_ID: {
            float v[] = {
                escena.light2_diffuse[0],  escena.light2_diffuse[1],
                escena.light2_diffuse[2],  escena.light2_diffuse[3] };

            v[0] *= light2_intensity;
            v[1] *= light2_intensity;
            v[2] *= light2_intensity;
            break;
        }
        case LIGHT2_AMBIENT_ID: {
            escena.light2_ambient[1] = escena.light2_ambient[0]; 
            escena.light2_ambient[2] = escena.light2_ambient[0]; 
            break;
        }
        case LIGHT2_DIFFUSE_ID: {
            escena.light2_diffuse[1] = escena.light2_diffuse[0]; 
            escena.light2_diffuse[2] = escena.light2_diffuse[0]; 
            break;
        }
        case LIGHT2_SPECULAR_ID: {
            escena.light2_specular[1] = escena.light2_specular[0]; 
            escena.light2_specular[2] = escena.light2_specular[0]; 
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 100.0;

            escena.camX = 0.0f;
            escena.camY = 0.0f;
            escena.camZ = 0.0f;

            escena.targetX = 0.0f;
            escena.targetY = 0.0f;
            escena.targetZ = 0.0f;

            escena.cameraDistance = 10.0f;

            escena.yaw   = 0.0f;
            escena.pitch = 0.0f;

            break;
        }
        case SEL_ID: {  
            TPrimitiva* selectedCar = escena.GetCar(escena.seleccion);

            selectedCar->colores[0][0] = 0.5f;
            selectedCar->colores[0][1] = 0.5f;
            selectedCar->colores[0][2] = 0.5f;
            selectedCar->colores[0][3] = 1.0f;

            escena.seleccion = sel;

            selectedCar = escena.GetCar(escena.seleccion);

            selectedCar->colores[0][0] = 0.7f;
            selectedCar->colores[0][1] = 1.0f;
            selectedCar->colores[0][2] = 0.1f;
            selectedCar->colores[0][3] = 1.0f;

            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case CAM_ID: {
            escena.camara = cam;
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case PROY_ID: {
            glutSetWindow( glui->get_glut_window_id() );
            escena.changeProy = true;
            escena.proyeccion = proy;
            break;
        }
        case FACES_ID: {

            std::cout << "CARAS INVERTIDAS \n";

            if ( faces == 0 ) {
                glFrontFace(GL_CW);
                std::cout << "Sentido horario\n";
            } else {
                glFrontFace(GL_CCW);
                std::cout << "Sentido antihorario\n";
            }

            if ( escena.culling == 0 ) {
                std::cout << "Culling desactivado\n";
                glDisable(GL_CULL_FACE);
            } else {
                std::cout << "Culling activado\n";
                glEnable(GL_CULL_FACE);
            }

            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case CULLING_ID: {

            std::cout << "CULLING! \n";


            if ( faces == 0 ) {
                glFrontFace(GL_CW);
                std::cout << "Sentido horario\n";
            } else {
                glFrontFace(GL_CCW);
                std::cout << "Sentido antihorario\n";
            }

            if ( escena.culling == 0 ) {
                std::cout << "Culling desactivado\n";
                glDisable(GL_CULL_FACE);
            } else {
                std::cout << "Culling activado\n";
                glEnable(GL_CULL_FACE);
            }

            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case VISUALIZATION_ID: {
            switch (visualization)
            {
            case 0:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_DEPTH_TEST);
                break;

            case 1:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;

            case 2:
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                break;
            
            default:
                break;
            }
        }
        case Z_BUFFER_ID: {
            
            std::cout << "Z-Buffer clickado:  \n";

            if ( escena.z_buffer == 0 ) {
                std::cout << "Z-Buffer desactivado \n";
                glDisable(GL_DEPTH_TEST);

            } else {
                std::cout << "Z-Buffer desactivado \n";
                glEnable(GL_DEPTH_TEST);

            }
            break;
        }
  }
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int xx, int yy )
{
    int x, y, ancho, alto;
    GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
    glViewport( x, y, ancho, alto );

    if (alto == 0) alto = 1;
    // !!!!! ATENCI�N: comprobar que alto no sea 0, sino divisi�n por 0 !!!!!!
    escena.xy_aspect = (float)ancho / (float)alto;

    switch (proy) {
    case 0:
        std::cout << "Proyeccion paralela seleccionada... \n";
        escena.projectionMatrix = glm::ortho(
            -10.0f, 10.0f,
            -10.0f / escena.xy_aspect, 10.0f / escena.xy_aspect,
            0.1f, 100.0f
        );
        break;

    case 1:
        std::cout << "Proyeccion paralela perspectiva...  \n";
        escena.projectionMatrix = glm::perspective(
            45.0f,
            escena.xy_aspect,
            0.1f,
            1000.0f
        );
        break;
    
    default:
        break;
    }

    glUseProgram(escena.shaderProgram->ReturnProgramID());
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion( int x, int y )
{
    int deltaX = x - gui.xIni;
    int deltaY = y - gui.yIni;

    deltaX *= escena.sensibility;
    deltaY *= escena.sensibility;
    
    if ( !escena.isShiftPressed && escena.leftButtonPressed ) { // ROTACION

        std::cout << "Rotacion!! \n";

        escena.yaw   += deltaX;
        escena.pitch += deltaY;

        if (escena.pitch > 89.0f) escena.pitch = 89.0f;
        if (escena.pitch < -89.0f) escena.pitch = -89.0f;

        if ( escena.isCtrlPressed ) {

            escena.targetX = escena.camX + cos(glm::radians(escena.pitch)) * sin(glm::radians(escena.yaw));
            escena.targetY = escena.camY + sin(glm::radians(escena.pitch));
            escena.targetZ = escena.camZ + cos(glm::radians(escena.pitch)) * cos(glm::radians(escena.yaw));

        } else {

            escena.camX = escena.targetX + escena.cameraDistance * cos(glm::radians(escena.pitch)) * sin(glm::radians(escena.yaw));
            escena.camY = escena.targetY + escena.cameraDistance * sin(glm::radians(escena.pitch));
            escena.camZ = escena.targetZ + escena.cameraDistance * cos(glm::radians(escena.pitch)) * cos(glm::radians(escena.yaw));
        
        }
    
    } else if ( escena.isShiftPressed && escena.leftButtonPressed ) { // TRASLACION

        std::cout << "Traslacion!! \n";

        if (escena.isCtrlPressed) {
            // Movimiento hacia adelante/atrás en el eje Z (dirección de la cámara)

            escena.camZ += deltaY * escena.sensibility;
            escena.targetZ += deltaY * escena.sensibility;

        } else {

            escena.camX += deltaX * escena.sensibility;
            escena.camY += deltaY * escena.sensibility;
            
            escena.targetX += deltaX * escena.sensibility;
            escena.targetY += deltaY * escena.sensibility;

        }

    }

    if ( escena.rightButtonPressed ) { // ESCALADO

        std::cout << "Escalado!! \n";

        escena.cameraDistance -= deltaY * 0.1f;
        if (escena.cameraDistance < 2.0f) escena.cameraDistance = 2.0f;

        escena.camX = escena.targetX + escena.cameraDistance * cos(glm::radians(escena.pitch)) * sin(glm::radians(escena.yaw));
        escena.camY = escena.targetY + escena.cameraDistance * sin(glm::radians(escena.pitch));
        escena.camZ = escena.targetZ + escena.cameraDistance * cos(glm::radians(escena.pitch)) * cos(glm::radians(escena.yaw));
    }

    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{

    int mod = glutGetModifiers();

    escena.isCtrlPressed = false;
    escena.isShiftPressed = false;

    if ( mod & GLUT_ACTIVE_CTRL ) {
        escena.isCtrlPressed = true;
        std::cout << "PRESSING CONTROL!!\n";
    }
    
    if ( mod & GLUT_ACTIVE_SHIFT ) {
        escena.isShiftPressed = true; 
        std::cout << "PRESSING SHIFT!!\n";
    }

    // Controlar el click izquierdo
    if ( button_state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && cam == 3 ) {
        gui.xIni = x;
        gui.yIni = y;

        escena.leftButtonPressed = true;
    }
    
    if (button_state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
        escena.Pick3D(x, y);
        escena.leftButtonPressed = false;

    }
    
    // Controlar el click derecho
    if ( button_state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON && cam == 3 ) {
        gui.xIni = x;
        gui.yIni = y;

        escena.rightButtonPressed = true;
    }

    if ( button_state == GLUT_UP && button == GLUT_RIGHT_BUTTON && cam == 3 ) {
        gui.xIni = x;
        gui.yIni = y;

        escena.rightButtonPressed = false;
    }
    
}

