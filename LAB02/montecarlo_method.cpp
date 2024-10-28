#include <mpi.h>
#include <iostream>
#include <random>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    long long int tosses = 5000;
    long long int local_in_circle = 0;
    long long int global_in_circle = 0;

    if (world_rank == 0)
    {
        std::cout << "Número de lanzamientos: " << tosses << std::endl;
    }

    MPI_Bcast(&tosses, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long long int local_tosses = tosses / world_size;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (long long int i = 0; i < local_tosses; i++)
    {
        double x = dist(gen);
        double y = dist(gen);
        if (x * x + y * y <= 1.0)
        {
            local_in_circle++;
        }
    }

    MPI_Reduce(&local_in_circle, &global_in_circle, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        double pi_estimate = (4.0 * global_in_circle) / tosses;
        std::cout << "Estimación de π: " << pi_estimate << std::endl;
    }

    MPI_Finalize();
    return 0;
}
