#include "../include/Camara.hpp"

Camara::Camara( 
    glm::vec3 Position, 
    glm::vec3 Front, 
    glm::vec3 Up, 
    float velocityCamera, float velocityMouse, 
    float yawMouse, float pitchMouse
)
{
    this->Position = Position;
    this->Front = Front;
    this->Up = Up;

    this->velocityCamera = velocityCamera;
    this->velocityMouse = velocityMouse;
    this->yawMouse = yawMouse;
    this->pitchMouse = pitchMouse;
}

void Camara::tecladoFunc(Movimiento tipo ,float deltatime){
    
    float velocidad = velocityCamera * deltatime;

    if(tipo == ADELANTE) Position += Front * velocidad;
    if(tipo == ATRAS) Position -= Front * velocidad;
    if(tipo == DERECHA) Position += glm::normalize(cross(Front, Up)) * velocidad;
    if(tipo == IZQUIERDA) Position -= glm::normalize(cross(Front, Up)) * velocidad;
    if(tipo == ARRIBA) Position.y += velocidad;
    if(tipo == ABAJO) Position.y -= velocidad;
}

void Camara::mouseFunc(float xoffset, float yoffset){
    xoffset *= velocityMouse;
    yoffset *= velocityMouse;

    yawMouse += xoffset;
    pitchMouse += yoffset;

    if (pitchMouse > 89.0f) pitchMouse = 89.0f;
    if (pitchMouse < -89.0f) pitchMouse = -89.0f;

    glm::vec3 front;
    front.x = glm::cos(glm::radians(yawMouse)) * glm::cos(glm::radians(pitchMouse));
    front.y = glm::sin(glm::radians(pitchMouse));
    front.z = glm::sin(glm::radians(yawMouse)) * glm::cos(glm::radians(pitchMouse));
    Front = glm::normalize(front);
}

glm::mat4 Camara::GetVistaMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}
