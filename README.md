
Simple log Analyzer project to practice C++
<img width="923" height="612" alt="notepad_riqYbYFlc7" src="https://github.com/user-attachments/assets/7f6fec04-c3de-4a88-9bcd-331c06e157c7" />
# Log Analyzer

A C++ command-line tool that reads a log file and produces a summary report including log level counts and the most frequently occurring messages.

## Build

```bash
make
```

## Usage

```bash
./log_analyzer <logfile>
```

### Example

```bash
./log_analyzer sample.log
```

**Expected output:**

```
========================================
          LOG ANALYSIS REPORT
========================================
File: sample.log
Total lines processed: 30

--- Log Level Counts ---
  ERROR: 6
  INFO: 16
  WARNING: 8

--- Top 5 Most Frequent Messages ---
  1. "Incoming request: GET /api/users" (x4)
  2. "Failed to connect to database" (x3)
  3. "Incoming request: POST /api/login" (x3)
  4. "Disk usage above 80%" (x2)
  5. "Retrying database connection (attempt 1)" (x2)
========================================
```

## Log Format

The analyzer expects logs in the following format:

```
[YYYY-MM-DD HH:MM:SS] [LEVEL] Message text
```

Where `LEVEL` is one of: `INFO`, `WARNING`, `ERROR`. Lines that don't match this format are classified as `UNKNOWN`.

## Clean

```bash
make clean
```
