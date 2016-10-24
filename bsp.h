#include "GL/gl.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define HEADER_LUMPS 64

enum
{
    LUMP_ENTITIES					= 0,	// *
    LUMP_PLANES						= 1,	// *
    LUMP_TEXDATA					= 2,	// *
    LUMP_VERTEXES					= 3,	// *
    LUMP_VISIBILITY					= 4,	// *
    LUMP_NODES						= 5,	// *
    LUMP_TEXINFO					= 6,	// *
    LUMP_FACES						= 7,	// *
    LUMP_LIGHTING					= 8,	// *
    LUMP_OCCLUSION					= 9,
    LUMP_LEAFS						= 10,	// *
    LUMP_FACEIDS					= 11,
    LUMP_EDGES						= 12,	// *
    LUMP_SURFEDGES					= 13,	// *
    LUMP_MODELS						= 14,	// *
    LUMP_WORLDLIGHTS				= 15,	//
    LUMP_LEAFFACES					= 16,	// *
    LUMP_LEAFBRUSHES				= 17,	// *
    LUMP_BRUSHES					= 18,	// *
    LUMP_BRUSHSIDES					= 19,	// *
    LUMP_AREAS						= 20,	// *
    LUMP_AREAPORTALS				= 21,	// *
    LUMP_UNUSED0					= 22,
    LUMP_UNUSED1					= 23,
    LUMP_UNUSED2					= 24,
    LUMP_UNUSED3					= 25,
    LUMP_DISPINFO					= 26,
    LUMP_ORIGINALFACES				= 27,
    LUMP_PHYSDISP					= 28,
    LUMP_PHYSCOLLIDE				= 29,
    LUMP_VERTNORMALS				= 30,
    LUMP_VERTNORMALINDICES			= 31,
    LUMP_DISP_LIGHTMAP_ALPHAS		= 32,
    LUMP_DISP_VERTS					= 33,		// CDispVerts
    LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS = 34,	// For each displacement
                                                //     For each lightmap sample
                                                //         byte for index
                                                //         if 255, then index = next byte + 255
                                                //         3 bytes for barycentric coordinates
    // The game lump is a method of adding game-specific lumps
    // FIXME: Eventually, all lumps could use the game lump system
    LUMP_GAME_LUMP					= 35,
    LUMP_LEAFWATERDATA				= 36,
    LUMP_PRIMITIVES					= 37,
    LUMP_PRIMVERTS					= 38,
    LUMP_PRIMINDICES				= 39,
    // A pak file can be embedded in a .bsp now, and the file system will search the pak
    //  file first for any referenced names, before deferring to the game directory
    //  file system/pak files and finally the base directory file system/pak files.
    LUMP_PAKFILE					= 40,
    LUMP_CLIPPORTALVERTS			= 41,
    // A map can have a number of cubemap entities in it which cause cubemap renders
    // to be taken after running vrad.
    LUMP_CUBEMAPS					= 42,
    LUMP_TEXDATA_STRING_DATA		= 43,
    LUMP_TEXDATA_STRING_TABLE		= 44,
    LUMP_OVERLAYS					= 45,
    LUMP_LEAFMINDISTTOWATER			= 46,
    LUMP_FACE_MACRO_TEXTURE_INFO	= 47,
    LUMP_DISP_TRIS					= 48,
    LUMP_PHYSCOLLIDESURFACE			= 49,	// deprecated.  We no longer use win32-specific havok compression on terrain
    LUMP_WATEROVERLAYS              = 50,
    LUMP_LEAF_AMBIENT_INDEX_HDR		= 51,	// index of LUMP_LEAF_AMBIENT_LIGHTING_HDR
    LUMP_LEAF_AMBIENT_INDEX         = 52,	// index of LUMP_LEAF_AMBIENT_LIGHTING

    // optional lumps for HDR
    LUMP_LIGHTING_HDR				= 53,
    LUMP_WORLDLIGHTS_HDR			= 54,
    LUMP_LEAF_AMBIENT_LIGHTING_HDR	= 55,	// NOTE: this data overrides part of the data stored in LUMP_LEAFS.
    LUMP_LEAF_AMBIENT_LIGHTING		= 56,	// NOTE: this data overrides part of the data stored in LUMP_LEAFS.

    LUMP_XZIPPAKFILE				= 57,   // deprecated. xbox 1: xzip version of pak file
    LUMP_FACES_HDR					= 58,	// HDR maps may have different face data.
    LUMP_MAP_FLAGS                  = 59,   // extended level-wide flags. not present in all levels
    LUMP_OVERLAY_FADES				= 60,	// Fade distances for overlays
};

#pragma pack(1)
struct lump_t
{
    int Offset;	// offset into file (bytes)
    int Length;	// length of lump (bytes)
    int Version;	// lump format version
    char FourCC[4];	// lump ident code
};

struct dheader_t
{
    int Ident;                // BSP file identifier
    int Version;              // BSP file version
    lump_t Lumps[HEADER_LUMPS];  // lump directory array
    int	MapRevision;          // the map's revision (iteration, version) number
};

struct dedge_t
{
    unsigned short V[2];	// vertex indices
};

struct dface_t
{
    unsigned short Planenum;		// the plane number
    unsigned char Side;			// faces opposite to the node's plane direction
    unsigned char OnNode;			// 1 of on node, 0 if in leaf

    int Firstedge;		// index into surfedges
    short Numedges;		// number of surfedges
    short Texinfo;		// texture info

    short Dispinfo;		// displacement info
    short SurfaceFogVolumeID;	// ?

    unsigned char Styles[4];		// switchable lighting info
    int Lightofs;		// offset into lightmap lump
    float Area;			// face area in units^2

    int LightmapTextureMinsInLuxels[2];	// texture lighting info
    int LightmapTextureSizeInLuxels[2];	// texture lighting info

    int OrigFace;		// original face this was split from

    unsigned short NumPrims;		// primitives
    unsigned short FirstPrimID;
    unsigned int SmoothingGroups;	// lightmap smoothing group
};

struct Vector3
{
    float x;
    float y;
    float z;
};

#pragma pack()

class BSP_H
{
public:
    BSP_H(const char *fileAddress);
    //void OGL_CreateFace();

public:
    dheader_t *Header;

    dface_t *Faces;

    Vector3 *Vertices;
    int *Surfedges;
    dedge_t *Edges;
};
