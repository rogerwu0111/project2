#include <iostream>

using namespace std;


// used to store the information of distance and predecessor
class block
{
private:
    int Distance;
    block* Predecessor;
public:

    block(int dis=-1, block* pre=NULL):Distance(dis), Predecessor(pre){}

    void setDistance(int dis){this->Distance = dis;}

    void setPredecessor(block* pre){this->Predecessor = pre;}

    int getDistance(){return this->Distance;}

    block* getPredecessor(){return this->Predecessor;}
};

void Initialize_BlockArray(int row, int col, block**arr, char** input)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (input[i][j] == '0') arr[i][j].setDistance(0);

            else if (input[i][j] == '1');

            else
            {
                arr[i][j].setDistance(0);

                arr[i][j].setPredecessor(&arr[i][j]);
            }
        }
    }
}

void BlockArray(int row, int col, block**arr, char** input)
{

}

int main()
{
    int rows, columns;

    cin >> rows;

    cin >> columns;

    char** input = new char*[rows];

    for (int i=0; i<rows; i++)
    {
        input[i] = new char[columns];
    }

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            cin >> input[i][j];
        }
    }

    block** dis_pre = new block* [rows];

    for (int i=0; i<rows; i++)
    {
        dis_pre[i] = new block[columns];
    }

    Initialize_BlockArray(rows, columns, dis_pre, input);

    return 0;
}