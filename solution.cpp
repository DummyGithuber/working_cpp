#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<iterator>
#include<tuple>

#define INPUT 1

class square_matrix{
  public:
    square_matrix(const char* input): matrix{input}, size{static_cast<std::size_t>(std::sqrt(matrix.size()))} {}
    char operator()(std::size_t row, std::size_t column) const{
      return matrix[row*size + column];
    }

    char& operator()(std::size_t row, std::size_t column){
      return matrix[row*size + column];
    }

    std::size_t get_size() const{
      return size;
    }

    std::string& get_string(){
      return matrix;
    }

  private:
    std::string matrix;
    const std::size_t size;
};

std::string print_spiral_matrix(square_matrix& matrix){
  const std::size_t matrix_size = matrix.get_size();
  std::vector<char> spiral(matrix_size * matrix_size);
  int u = 0, d = matrix_size - 1, l = 0, r = matrix_size - 1, k = 0;
  while (true) {
      // up
      for (int col = l; col <= r; col++) spiral[k++] = matrix(u, col);
      if (++u > d) break;
      // right
      for (int row = u; row <= d; row++) spiral[k++] = matrix(row, r);
      if (--r < l) break;
      // down
      for (int col = r; col >= l; col--) spiral[k++] = matrix(d, col);
      if (--d < u) break;
      // left
      for (int row = d; row >= u; row--) spiral[k++] = matrix(row, l);
      if (++l > r) break;
  }
  return std::string(spiral.begin(), spiral.end());
}

void rotate_matrix_180(square_matrix& matrix){
  const std::size_t size = matrix.get_size();
  for (std::size_t index1 = 0, cntSwap = 0, maxSwap = (size*size) / 2; cntSwap < maxSwap; ++index1)
      for (std::size_t index2 = 0; index2 < size && cntSwap < maxSwap; ++index2, ++cntSwap)
          std::swap(matrix(index1, index2), matrix(size - index1 - 1, size - index2 - 1));
}

int main(int _, char* argv[]){
  std::ignore = _;

  square_matrix matrix{argv[INPUT]};
  rotate_matrix_180(matrix);
  std::cout << print_spiral_matrix(matrix);
}
