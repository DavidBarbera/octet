#define ANGLE 45
#define PI 3.1415926535897932384626433832795028841971693993751
#define RANGLE ANGLE*PI/180

namespace octet {
	class TurtleState {
		vec3 position;
		float angle;
	public:

		vec3 pos() {
			return position;
		}
		float ang() {
			return angle;
		}
		void setpostition(vec3 xyz) {
			position = xyz;
		}
		void setangle(float alpha) {
			angle = alpha;
		}
		void setstate(vec3 xyz, float alpha) {
			position = xyz;
			angle = alpha;
		}
	};

}