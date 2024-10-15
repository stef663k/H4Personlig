colors_setup(){
    tput sgr0
    BG_COLOR=$(tput setab 4)
    FG_COLOR=$(tput setaf 7)
    HIGHLIGHT=$(tput setab 3)
    RESET=$(tput sgr0)
}

display_menu(){
  clear
  echo "${BG_COLOR}${FG_COLOR}"
  tput cup 3 15
  echo "Welcome to my menu"

  tput cup 5 10
  echo "List of PIDs"

  tput cup 6 10
  echo "Kill a PID"

  tput cup 7 10
  echo "System information"
	
  tput cup 8 10
  echo "File information"

  tput cup 9 10
  echo "Exit"

  tput cup 10 10
  echo "${Reset}" 
}

read_choice(){
  tput cup 11 10
  echo -n "Choose a task (1-5): "
  read choice
}

handle_choice(){
  case $choice in
        1) 
	   echo "Listing all running services (process names and PIDs: )"
	   ps -e -o pid,comm
           read -p "press any key to return to menu: "
           ;;
        2) 
	   echo "Please enter the number of the PID you want to kill: "
           read pid
	   echo "Are you sure you want to kill this process with PID $pid? (y/n): "
	   read confirmation
	   
	   if [ "${confirmation}" = "y" ]; then
	  
	     if kill $pid > /dev/null 2>&1; then
		echo "process with $pid was successfully killed."
	     else
		echo "Something whent wrong. We could not kill process with $pid"
	     fi

	  else
		echo "The process will not be killed"
	  fi

	  read -p "Press any key to return to menu"
	   
           ;;
        3) 
	  echo "fetching essential system information..."
	  
	  echo "CPU model: $(lscpu | grep: 'Model name:' | awk -F ':' '{print $2}' | xargs)"
	 
	  total_ram=$(free -h | grep 'Mem:' | awk '{print $2}')
	  used_ram=$(free -h | grep 'Mem:' | awk '{print $3}')
	  echo "Total Ram: $total_ram"
	  echo "Used Ram: $used_ram"

	  disk_space=$(df -h --output=avail / | tail -n 1)
	  echo "Available disk space: $disk_space"

	  read -p "Press any key to return to menu"
           ;;
	4)
	   echo "Please enter the name of the file to search for (you can use wildcards, e.g., '*.txt'): "
	    read filename

	    echo "Searching for occurrences of '$filename' in the home directory..."

	    temp_file=$(mktemp)
	    find ~ -name "$filename" -print > "$temp_file" 2>/dev/null

	    echo "Debug: Checking results in $temp_file"
	    cat "$temp_file"  

	    if [ -s "$temp_file" ]; then
	        while read -r filepath; do
	            filesize=$(stat -c%s "$filepath")  
	            creation_date=$(stat -c%y "$filepath")  
	            echo "Found: $filepath"
	            echo "Size: $filesize bytes"
	            echo "Creation Date: $creation_date"
	            echo "-----------------------------"
	        done < "$temp_file"
	    else
	        echo "No occurrences of '$filename' found."
	    fi

	    rm "$temp_file"

	    read -p "Press any key to return to the menu..."
	    ;;
        5) echo "Exiting the program. Bye bye!"
           exit 0
           ;;
	*) echo "Invalid option. Try again!" ;;
	esac
}

setup_colors
while true; do
  display_menu
  read_choice
  handle_choice
done
x
