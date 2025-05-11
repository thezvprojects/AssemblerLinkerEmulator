nano ~/.bashrc

Active aliases (for logging, output to new terminal):

alias runparsercheck='logfile="logs/outputlog*$(date +%F*%H-%M-%S).txt"; mkdir -p logs && ./parser input.txt | tee "$logfile" | tee >(gnome-terminal -- bash -c "cat \"$logfile\"; exec bash")'
