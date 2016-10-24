#include "bsp.h"

BSP_H::BSP_H(const char *fileAddress)
{
    this->Header = new dheader_t();

    ifstream *fileReader = new ifstream(fileAddress, ios::binary);
    fileReader->read((char *)this->Header, sizeof(dheader_t));

    int numFaces = Header->Lumps[LUMP_FACES].Length / sizeof(dface_t);
    this->Faces = new dface_t[numFaces];

    fileReader->seekg(Header->Lumps[LUMP_FACES].Offset, ios::beg);
    fileReader->read((char *)this->Faces, sizeof(dface_t) * numFaces);

    int numVertices = Header->Lumps[LUMP_VERTEXES].Length / sizeof(Vector3);
    this->Vertices = new Vector3[numVertices];

    fileReader->seekg(Header->Lumps[LUMP_VERTEXES].Offset, ios::beg);
    fileReader->read((char *)this->Vertices, sizeof(Vector3) * numVertices);

    int numSurfedges = Header->Lumps[LUMP_SURFEDGES].Length / sizeof(int);
    this->Surfedges = new int[numSurfedges];

    fileReader->seekg(Header->Lumps[LUMP_SURFEDGES].Offset, ios::beg);
    fileReader->read((char *)this->Surfedges, sizeof(int) * numSurfedges);

    int numEdges = Header->Lumps[LUMP_EDGES].Length / sizeof(dedge_t);
    this->Edges = new dedge_t[numEdges];

    fileReader->seekg(Header->Lumps[LUMP_EDGES].Offset, ios::beg);
    fileReader->read((char *)this->Edges, sizeof(dedge_t) * numEdges);

    fileReader->close();

    delete [] this->Header, this->Faces, this->Vertices, this->Surfedges, this->Edges;
}


