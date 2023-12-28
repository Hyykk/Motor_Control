#include "stdafx.h"
#include "ODE.h"
#include "SystemMemory.h"
#include "DataType.h"

#ifndef DRAWSTUFF_TEXTURE_PATH
#define DRAWSTUFF_TEXTURE_PATH "./../ode-0.13/drawstuff/textures"
#endif

#define GRAVITY 9.81
#define MAX_JOINT_NUM 3

#define DEG2RAD 0.0174533
#define RAD2DEG 57.2958

dsFunctions g_Fn;

static dWorldID g_World;
static dSpaceID g_Space;
static dJointGroupID g_Contactgroup;
static dGeomID g_Ground;

Object g_oObj[MAX_JOINT_NUM + 1];
static dJointID g_oJoint[MAX_JOINT_NUM + 1];

double g_tar_q[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0};
double g_cur_q[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0};

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
	int i;
	static const int N = 5;
	dContact contact[N];
	if ((g_Ground == o1) || (g_Ground == o2))
	{
		int isGround = ((g_Ground == o1) || (g_Ground == o2));
		int n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));
		if (isGround)
		{
			for (int i = 0; i < n; i++)
			{
				contact[i].surface.mu = 0.1;
				contact[i].surface.mode = dContactBounce;
				contact[i].surface.bounce = 0.0;
				contact[i].surface.bounce_vel = 0.0;
				dJointID c = dJointCreateContact(g_World, g_Contactgroup,
					&contact[i]);
				dJointAttach(c, dGeomGetBody(contact[i].geom.g1),
					dGeomGetBody(contact[i].geom.g2));
			}
		}
	}
}

void InitDrawStuff() {

	g_Fn.version = DS_VERSION;
	g_Fn.start = &StartDrawStuff;
	g_Fn.step = &SimLoopDrawStuff;
	g_Fn.command = &CommandDrawStuff;
	g_Fn.stop = StopDrawStuff;
	g_Fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;
}


void InitODE() {

	//TO DO
	// setDrawStuff();
	dInitODE();
	g_World = dWorldCreate();
	g_Space = dHashSpaceCreate(0);
	g_Contactgroup = dJointGroupCreate(0);
	g_Ground = dCreatePlane(g_Space, 0, 0, 1, 0);
	dWorldSetGravity(g_World, 0, 0, -GRAVITY);
	dWorldSetERP(g_World, 1.0);
	dWorldSetCFM(g_World, 1e-5);
}



void RunODE(size_t width, size_t height) {

	//TO DO
	InitDrawStuff();
	InitODE();

	InitRobot();

	// Run Simulation
	dsSimulationLoop(0, 0, width, height, &g_Fn);
}



void ReleaseODE() {

	dJointGroupDestroy(g_Contactgroup);
	dSpaceDestroy(g_Space);
	dWorldDestroy(g_World);
	dCloseODE();
}



void StartDrawStuff() {

	//TO DO
	float dPos[3] = { 0.0, 2.5, 2.5 };
	float dRot[3] = { -90.0, -30.0, 0.0 };
	dsSetViewpoint(dPos, dRot);
}


void SimLoopDrawStuff(int pause) 
{

	//TO DO
	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	g_tar_q[0] = jointData.Q_tar[0];
	g_tar_q[1] = jointData.Q_tar[1];
	g_tar_q[2] = jointData.Q_tar[2];

	jointData.Q_cur[0] = g_cur_q[0];
	jointData.Q_cur[1] = g_cur_q[1];
	jointData.Q_cur[2] = g_cur_q[2];

	SET_SYSTEM_MEMORY("JointData", jointData);

	//dSpaceCollide(g_Space, 0, &nearCallback);

	dReal r, length;
	PControl();
	double dt = 0.01;
	dWorldStep(g_World, dt);

	// 1번째 body
	dsSetColor(1.0, 1.0, 1.0);
	dGeomCapsuleGetParams(g_oObj[0].geom, &r, &length);
	dsDrawCapsuleD(dBodyGetPosition(g_oObj[0].body), dBodyGetRotation(g_oObj[0].body), (float)length, (float)r);

	// 2번째 body
	dsSetColor(0.5, 0.7, 0.2);
	dGeomCapsuleGetParams(g_oObj[1].geom, &r, &length);
	dsDrawCapsuleD(dBodyGetPosition(g_oObj[1].body), dBodyGetRotation(g_oObj[1].body), (float)length, (float)r);

	//3번째 body	
	dsSetColor(0.9, 0.7, 0.2);
	dGeomCapsuleGetParams(g_oObj[2].geom, &r, &length);
	dsDrawCapsuleD(dBodyGetPosition(g_oObj[2].body), dBodyGetRotation(g_oObj[2].body), (float)length, (float)r);
}



void CommandDrawStuff(int cmd) {

	//TO DO
}



void StopDrawStuff() {

	//TO DO

}


void InitRobot()
{

	//TO DO
	dMass mass;
	dMatrix3 R;

	dReal x[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal y[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal z[MAX_JOINT_NUM] = { 0.25, 1.0, 1.75 };

	dReal ori_x[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal ori_y[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal ori_z[MAX_JOINT_NUM] = { 1.0, 1.0, 1.0 };
	dReal ori_q[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };

	dReal length[MAX_JOINT_NUM] = { 0.5, 1.0, 0.5 };
	dReal weight[MAX_JOINT_NUM] = { 0.5, 1.0, 0.5 };

	dReal r[MAX_JOINT_NUM];

	for (int i = 0; i < MAX_JOINT_NUM; i++)
	{
		r[i] = 0.125;
	}
	//Body 생성
	for (int i = 0; i < MAX_JOINT_NUM; i++)
	{
		g_oObj[i].body = dBodyCreate(g_World);
		dBodySetPosition(g_oObj[i].body, x[i], y[i], z[i]);
		dMassSetCapsuleTotal(&mass, weight[i], 1, r[i], length[i]);
		g_oObj[i].geom = dCreateCapsule(g_Space, r[i], length[i]);
		dGeomSetBody(g_oObj[i].geom, g_oObj[i].body);
		dRFromAxisAndAngle(R, ori_x[i], ori_y[i], ori_z[i], ori_q[i]);
	}

	dReal c_x[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal c_y[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal c_z[MAX_JOINT_NUM] = { 0.0, 0.5, 1.5 };

	dReal axis_x[MAX_JOINT_NUM] = { 0.0, 0.0, 0.0 };
	dReal axis_y[MAX_JOINT_NUM] = { 0.0, -1.0, -1.0 };
	dReal axis_z[MAX_JOINT_NUM] = { 1.0, 0.0, 0.0 };

	g_oJoint[0] = dJointCreateFixed(g_World, 0);
	dJointAttach(g_oJoint[0], 0, g_oObj[0].body);
	dJointSetFixed(g_oJoint[0]);
	for (int i = 1; i < MAX_JOINT_NUM; i++)
	{
			g_oJoint[i] = dJointCreateHinge(g_World, 0);
			dJointAttach(g_oJoint[i], g_oObj[i].body, g_oObj[i - 1].body);
			dJointSetHingeAnchor(g_oJoint[i], c_x[i], c_y[i], c_z[i]);
			dJointSetHingeAxis(g_oJoint[i], axis_x[i], axis_y[i], axis_z[i]);
	}
}

void PControl()
{
	//TO DO
	dReal Kp = 0.1, fMax = 100.0;
	dReal a_error_q[MAX_JOINT_NUM];
	for (int i = 1; i < MAX_JOINT_NUM; i++)
	{
		g_cur_q[i] = dJointGetHingeAngle(g_oJoint[i]);
		a_error_q[i] = g_tar_q[i] * DEG2RAD - g_cur_q[i];
		dJointSetHingeParam(g_oJoint[i], dParamVel, Kp * a_error_q[i]);
		dJointSetHingeParam(g_oJoint[i], dParamFMax, fMax);
	}
}