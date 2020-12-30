for rho in 1 2 3 4
  do
    {
      for v in 1 2 3 4
        do
          {
            ./first_task 1.4 $1 100 10000 $v $rho $2
          }
	done
    }
  done 

echo "done";

