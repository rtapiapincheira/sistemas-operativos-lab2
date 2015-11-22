using System.Threading;

/**
 * Thread a-la-Java.
 */
public abstract class MyThread {
	
	private Thread mThread;
	
	public MyThread() {
		mThread = new Thread(Run);
	}
	
	public void Start() {
		mThread.Start();
	}
	
	public void Join() {
		mThread.Join();
	}
	
	public abstract void Run();
}