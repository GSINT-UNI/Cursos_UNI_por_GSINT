#define TERRAIN_ERROR_INVALID_PARAM		-5
#define TERRAIN_ERROR_LOADING_IMAGE		-4
#define TERRAIN_ERROR_MEMORY_PROBLEM	-3
#define	TERRAIN_ERROR_NOT_SAVED			-2
#define TERRAIN_ERROR_NOT_INITIALISED	-1
#define TERRAIN_OK						 0

/* Functions for fault algorithm */

#define STEP	1
#define SIN		2
#define COS		3
#define CIRCLE  4
#define MPD		5
#define RandomDirection 6

float terrainGetWidth();
float terrainGetLength();


int terrainLoadFromImage(char *filename, int normals);
int terrainCreateDL(int lighting,int faceType);
void terrainDestroy();
int terrainScaleHeights(float min,float max);
float terrainGetHeight(int x, int z);
int terrainSimulateLighting(int sim);
void terrainLightPosition(float x, float y, float z,float w);
void terrainDiffuseColor(float r, float g, float b);
void terrainAmbientColor(float r, float g, float b);
void terrainSetNormals(int normals);

void terrainSetOrigin(float x,float y,float z);
void terrainSetScaleXZ(float x, float z);

void terrainSmooth(float k);

void terrainResetFilter();
void terrainSetFilter(float *newFilter);
int terrainApplyFilter();


void terrainInit(int x, int y);
int terrainIterateFault(int numIterations);
void terrainSetRandomSeed(int rs);
void terrainSetMaxDisp(float maxdisp1);
void terrainSetMinDisp(float mindisp1);
void terrainSetWaveSize(float ws);
void terrainSetItMinDisp(int it);
void terrainSetFunction(int fun);
void terrainSetCircleSize(float cs);
int terrainIterateCircles(int numIterations);
int terrainIterate(int numIt);
int terrainIterateMidPointDisplacement(int steps,float maxDispH,float roughness);
void terrainSetRoughness(float r);

#define ROLL	0
#define STICK	1

void terrainSetParticleMode(int mode);
int terrainIterateParticleDeposition(int numIt);

int terrainSaveAsTGA(char *filename);
