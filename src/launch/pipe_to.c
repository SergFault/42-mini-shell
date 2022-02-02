

/* change to structures */
int pipe_to(from_command *first, char *to_command){

	int pipe_fd[2];
	pipe(pipe_fd);

	int pid = fork();
	if (!pid)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(from_command, argv, env);
	}
	close(pipe_fd[1]);
	pid = fork();
	if (!pid)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve(to_command, argv, env);
	}
	close(pipe_fd[0]);
	wait(0);
}