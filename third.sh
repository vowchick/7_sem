for K in 1 2 3 4 5 6 7 8 9 10
  do
    {
      for mu in 0.1 0.01 0.001
        do
          {
            ./first_task 1.4 $mu 100 10000 $K $1
          }
        done
    }
  done 

echo "done";
