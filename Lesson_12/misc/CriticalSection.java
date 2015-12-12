package orcchg;

public class CriticalSection {
  private static final long LOOPS = 100_000_000l;
  private volatile long mValue = 0;

  private Object mLock = new Object();

  private void add() {
    for (long i = 0; i < LOOPS; ++i) {
      synchronized(mLock) {
        ++mValue;
      }
    }
  }

  private void sub() {
    for (long i = 0; i < LOOPS; ++i) {
      synchronized(mLock) {
        --mValue;
      }
    }
  }

  private long getValue() {
    return mValue;
  }

  /* Worker threads */
  // --------------------------------------------
  private static class AddRunnable implements Runnable {
    private CriticalSection mResources;

    private AddRunnable(CriticalSection resources) {
      mResources = resources;
    }

    @Override
    public void run() {
      mResources.add();
    }
  };

  private static class SubRunnable implements Runnable {
    private CriticalSection mResources;

    private SubRunnable(CriticalSection resources) {
      mResources = resources;
    }

    @Override
    public void run() {
      mResources.sub();
    }
  };

  /* Main */
  // --------------------------------------------------------------------------
  public static void main(String[] args) {
    CriticalSection resources = new CriticalSection();

    long start = System.currentTimeMillis();

    Thread addThread = new Thread(new AddRunnable(resources));
    Thread subThread = new Thread(new SubRunnable(resources));

    addThread.start();
    subThread.start();

    try {
      addThread.join();
      subThread.join();
    } catch (InterruptedException e) {
      System.err.println("Exception: " + e.toString());
    }

    long elapsed = System.currentTimeMillis() - start;
    System.out.println("Value: " + resources.getValue() + ", Time: " + elapsed);
  }
}

