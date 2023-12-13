#pragma once

#include "Barrier.h"
#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"

namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};


class SleepJobBarrier : public Job {
	Color pixel;
	Color *ret;
	Color *pixels;
	Scene scene;
	const Scene::screen_t & screen;
	Barrier *barrier;

	Color calcul (Color pixel) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);

		// pour chaque pixel, calculer sa couleur
		for (int x =0 ; x < scene.getWidth() ; x++) {
			for (int  y = 0 ; y < scene.getHeight() ; y++) {
				// le point de l'ecran par lequel passe ce rayon
				auto & screenPoint = screen[y][x];
				// le rayon a inspecter
				Rayon  ray(scene.getCameraPos(), screenPoint);

				int targetSphere = findClosestInter(scene, ray);

				if (targetSphere == -1) {
					// keep background color
					continue ;
				} else {
					const Sphere & obj = *(scene.begin() + targetSphere);
					// pixel prend la couleur de l'objet
					Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
					// le point de l'image (pixel) dont on vient de calculer la couleur
					Color & pixel = pixels[y*scene.getHeight() + x];
					// mettre a jour la couleur du pixel dans l'image finale.
					pixel = finalcolor;
				}
			}
		}

	}

public :
	SleepJobBarrier(Color pixel, Color *ret, Color *pixels, Scene scene,
		Scene::screen_t screen, Barrier *b) :
		pixel(pixel), ret(ret), pixels(pixels), scene(scene), screen(screen), barrier(b) {}
	void run () {
		*ret = calcul(pixel);
		barrier->done();
	}
	~SleepJobBarrier(){}
};

}
