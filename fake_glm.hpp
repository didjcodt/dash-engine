/*
 * This is a fake glm lib just to get some of the vec3 functionnalities
 * because this lib cannot be added without accessing the makefile.
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

// TODO: Check if glm is installed and include glm instead of this file

#pragma once

template <class T>
class vec3 {
	private:
		T x, y, z;
	public:
		vec3() { x = y = z = 0; }
		vec3(T xValue, T yValue, T zValue) {
			x = xValue;
			y = yValue;
			z = zValue;
		}

		// Getters and Setters
		// For cartesian
		T getX() const { return x; }
		T getY() const { return y; }
		T getZ() const { return z; }

		void set(T xValue, T yValue, T zValue) {
			setX(xValue);
			setY(yValue);
			setZ(zValue);
		}
		void setX(T xValue) { x = xValue; }
		void setY(T yValue) { y = yValue; }
		void setZ(T zValue) { z = zValue; }

		// For Spherical
		T getR()     const { return ;}
		T getTheta() const { return ;}
		T getPhi()   const { return ;}

		void setPolar(T rad, T theta, T phi) {
			x = rad * sin(theta) * cos(phi);
			y = rad * sin(theta) * sin(phi);
			z = rad * cos(theta);
		}

		// Operators
		vec3 operator==(const vec3 &vector) {
			return (vector.getX()==x) &&
				   (vector.getY()==y) &&
				   (vector.getZ()==z);
		}
};

template <class T>
class vec4 {
	private:
		T x, y, z, t;
	public:
		vec4() { x = y = z = t = 0; }
		vec4(T xValue, T yValue, T zValue, T tValue) {
			x = xValue;
			y = yValue;
			z = zValue;
			t = tValue;
		}

		// Getters and Setters
		// For cartesian
		T getX() const { return x; }
		T getY() const { return y; }
		T getZ() const { return z; }
		T getT() const { return t; }

		void set(T xValue, T yValue, T zValue, T tValue) {
			setX(xValue);
			setY(yValue);
			setZ(zValue);
			setT(tValue);
		}
		void setX(T xValue) { x = xValue; }
		void setY(T yValue) { y = yValue; }
		void setZ(T zValue) { z = zValue; }
		void setT(T tValue) { t = tValue; }

		// Operators
		vec4 operator==(const vec4 &vector) {
			return (vector.getX()==x) &&
				   (vector.getY()==y) &&
				   (vector.getZ()==z) &&
				   (vector.getT()==t);
		}
};
