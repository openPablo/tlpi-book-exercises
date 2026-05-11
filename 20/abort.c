/*

    Exercise: implement abort(). from the man page:
The abort() function first unblocks the SIGABRT signal, and then raises that
signal for the calling process (as though raise(3) was called).  This results in
the abnormal termination of the process unless the SIGABRT signal is caught and
the signal handler does not return (see longjmp(3)).

If  the  SIGABRT signal is ignored, or caught by a handler that returns, the
abort() function will still termi‐ nate the process.  It does this by restoring
the default disposition for SIGABRT and then  raising  the  signal for a second
time.

As  with  other  cases  of  abnormal termination the functions registered with
atexit(3) and on_exit(3) are not called.
 */

#include <bits/types/sigset_t.h>
#include <signal.h>

void abort_pablo() {
  sigset_t newmask, oldmask;
  sigemptyset(&newmask);
  sigemptyset(&oldmask);
  sigaddset(&newmask, SIGABRT);
  sigprocmask(SIG_UNBLOCK, &newmask, &oldmask);
  if (raise(SIGABRT) == 0) {
    signal(SIGABRT, SIG_DFL);
  }
}
