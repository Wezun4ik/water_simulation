#include "terrain.hpp"

heightmap::heightmap(const std::string& map_file_path)
{
	std::ifstream fout;
	std::vector<int> 	temp;
	fout.open(map_file_path);
	if (fout.is_open())
	{
		size_t		height = 0;
		for (;fout.good(); ++height)
		{
			std::string		print;
			getline(fout, print);
			if (print.empty())
			{
				--height;
				continue;
			}
			std::istringstream	ss(print);
			size_t width = 0;
			for (;ss.good(); ++width)
			{
				int		integer = 0;
				if (!(ss >> integer))
					break;
				temp.push_back(integer);
			}
			if (this->width == 0)
				this->width = width;
			else if (this->width != 0 && this->width != width)
			{
				std::invalid_argument	exc("File has different number of arguments in row: " + std::to_string(height + 1));
				throw (exc);
			}
		}
		this->height = height;
		std::cout << this->height << " " << this->width << std::endl;
		this->data = new int*[height];
		for (size_t i = 0; i < height; ++i)
		{
			this->data[i] = new int[width];
			for (size_t k = 0; k < width; ++k)
				this->data[i][k] = temp[width * i + k];
		}
	}
}
