#ifndef GENERAL_3D_MODEL
#define GENERAL_3D_MODEL


class General3dModel{
	public:
		General3dModel(void);
		virtual ~General3dModel(void) = 0;
		virtual void drawModel(void) = 0;
};


#endif