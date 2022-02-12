#include "Camera.hpp"

//Camera::Camera(Point camera_pos, Point lookAt, Point viewUp, double gradeTam, double distGrade, int furos)
//: coordCamera(camera_pos), lookAt(lookAt), viewUp(viewUp), qtdFuros(furos) {
//	olho = Point(0, 0, 0);
//
//	kc = (camera_pos - lookAt).normalized();
//	ic = kc.cross(viewUp - coordCamera).normalized();
//	jc = ic.cross(kc);
//
//	double deslocamento = gradeTam / qtdFuros;
//	double x, y, z = distGrade;
//
//	// AQUI EU ALOCO ESPAÇO PRA TELA DE PIXELS
//
//	alocar_camera(gradeCamera, furos);
//
//	for (int j = 0; j < furos; ++j) {
//		x = gradeTam / 2 - deslocamento - j * deslocamento;
//		for (int k = 0; k < furos; ++k) {
//			y = -gradeTam / 2 + deslocamento + k * deslocamento;
//
//			gradeCamera[k][j] = Point(x, y, z);
//		}
//	}
//}

Camera::Camera() {};

Camera::Camera(Point eye, Point lookAt, Point viewUp, int d, int plano_tamanho) : d(d), plano_tamanho(plano_tamanho) {
    this->eye    = eye;
    this->lookAt = lookAt;
    this->viewUp = viewUp;

    this->k = (eye - lookAt).normalized();

    this->i = (viewUp.cross(k)).normalized();
    this->j = (k.cross(i)).normalized();
};

Matriz Camera::worldToCamera() {
    Matriz worldToCamera;
    worldToCamera << i[0], i[1], i[2], -i.dot(eye),
        j[0], j[1], j[2], -j.dot(eye),
        k[0], k[1], k[2], -k.dot(eye),
        0, 0, 0, 1;
    return worldToCamera;
};

Matriz Camera::cameraToWorld() {
    Matriz cameraToWorld;
    cameraToWorld << i[0], j[0], k[0], eye[0],
        i[1], j[1], k[1], eye[1],
        i[2], j[2], k[2], eye[2],
        0, 0, 0, 1;
    return cameraToWorld;
};

void Camera::update() {
    this->k = (eye - lookAt).normalized();

    this->i = (viewUp.cross(k)).normalized();
    this->j = (k.cross(i)).normalized();
};

void Camera::moveX(float x)
{
    this->eye.x() += x;
    update();
};

void Camera::moveY(float y)
{
    this->eye.y() += y;
    update();
};

void Camera::moveZ(float z)
{
    this->eye.z() += z;
    update();
};

void Camera::moveTo(Point eye)
{
    this->eye = eye;
    update();
};
