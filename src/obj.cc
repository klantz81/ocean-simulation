#include "obj.h"

cObj::cObj(std::string filename) {
	std::ifstream ifs(filename.c_str(), std::ifstream::in);
	std::string line, key;
	while (ifs.good() && !ifs.eof() && std::getline(ifs, line)) {
		key = "";
		std::stringstream stringstream(line);
		stringstream >> key >> std::ws;
		
		if (key == "v") { // vertex
			vertex_obj v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			vertices.push_back(v);
		} else if (key == "vp") { // parameter
			vertex_obj v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			parameters.push_back(v);
		} else if (key == "vt") { // texture coordinate
			vertex_obj v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			texcoords.push_back(v);
		} else if (key == "vn") { // normal
			vertex_obj v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			v.normalize();
			normals.push_back(v);
		} else if (key == "f") { // face
			face_obj f; int v, t, n;
			while (!stringstream.eof()) {
				stringstream >> v >> std::ws;
				f.vertex.push_back(v-1);
				if (stringstream.peek() == '/') {
					stringstream.get();
					if (stringstream.peek() == '/') {
						stringstream.get();
						stringstream >> n >> std::ws;
						f.normal.push_back(n-1);
					} else {
						stringstream >> t >> std::ws;
						f.texture.push_back(t-1);
						if (stringstream.peek() == '/') {
							stringstream.get();
							stringstream >> n >> std::ws;
							f.normal.push_back(n-1);
						}
					}
				}
			}
			faces.push_back(f);
		} else {

		}
	}
	ifs.close();
	std::cout << "               Name: " << filename << std::endl;
	std::cout << "           Vertices: " << number_format(vertices.size()) << std::endl;
	std::cout << "         Parameters: " << number_format(parameters.size()) << std::endl;
	std::cout << "Texture Coordinates: " << number_format(texcoords.size()) << std::endl;
	std::cout << "            Normals: " << number_format(normals.size()) << std::endl;
	std::cout << "              Faces: " << number_format(faces.size()) << std::endl << std::endl;
}

cObj::~cObj() {
	vertices.clear();
	texcoords.clear();
	normals.clear();
	faces.clear();
}

void cObj::setupBufferObjects() {
	int size = faces.size();
	v_obj *vertices_ = new v_obj[size*3];
	unsigned int *indices_ = new unsigned int[size*3];
	for (int j = 0, i = 0; i < size; i++) {
		vertices_[j].x  = vertices[faces[i].vertex[0]].v[0];
		vertices_[j].y  = vertices[faces[i].vertex[0]].v[1];
		vertices_[j].z  = vertices[faces[i].vertex[0]].v[2];
		vertices_[j].nx = normals[faces[i].normal[0]].v[0];
		vertices_[j].ny = normals[faces[i].normal[0]].v[1];
		vertices_[j].nz = normals[faces[i].normal[0]].v[2];
		indices_[j]     = j;
		j++;

		vertices_[j].x  = vertices[faces[i].vertex[1]].v[0];
		vertices_[j].y  = vertices[faces[i].vertex[1]].v[1];
		vertices_[j].z  = vertices[faces[i].vertex[1]].v[2];
		vertices_[j].nx = normals[faces[i].normal[1]].v[0];
		vertices_[j].ny = normals[faces[i].normal[1]].v[1];
		vertices_[j].nz = normals[faces[i].normal[1]].v[2];
		indices_[j]     = j;
		j++;

		vertices_[j].x  = vertices[faces[i].vertex[2]].v[0];
		vertices_[j].y  = vertices[faces[i].vertex[2]].v[1];
		vertices_[j].z  = vertices[faces[i].vertex[2]].v[2];
		vertices_[j].nx = normals[faces[i].normal[2]].v[0];
		vertices_[j].ny = normals[faces[i].normal[2]].v[1];
		vertices_[j].nz = normals[faces[i].normal[2]].v[2];
		indices_[j]     = j;
		j++;
	}

	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, size*3*sizeof(v_obj), vertices_, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*3*sizeof(unsigned int), indices_, GL_STATIC_DRAW);
	
	delete [] vertices_;
	delete [] indices_;
}

void cObj::render(GLint vertex, GLint normal) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(v_obj), 0);
	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(v_obj), (char *)NULL + 12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glDrawElements(GL_TRIANGLES, faces.size()*3, GL_UNSIGNED_INT, 0);
}

void cObj::releaseBufferObjects() {
	glDeleteBuffers(1, &vbo_indices);
	glDeleteBuffers(1, &vbo_vertices);
}
