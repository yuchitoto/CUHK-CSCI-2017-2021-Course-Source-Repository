!
! CSCI3180 Principles of Programming Languages
!
! --- Declaration ---
!
! I declare that the assignment here submitted is original except for source
! material explicitly acknowledged. I also acknowledge that I am aware of
! University policy and regulations on honesty in academic work, and of the
! disciplinary guidelines and procedures applicable to breaches of such policy
! and regulations, as contained in the website
! http://www.cuhk.edu.hk/policy/academichonesty/
!
! Assignment 1
! Name : Wong Sin Yi
! Student ID : 1155110677
! Email Addr : sywong8@cse.cuhk.edu.hk
!

      PROGRAM MAIN
      IMPLICIT NONE   

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!       variable declaration       !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      CHARACTER    JUNK

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!        For reading file          !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      CHARACTER*30 FILE1
      CHARACTER*30 FILE2
      CHARACTER*30 FILE3

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!    For reading employees file    !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      EMFILE
      INTEGER      EMIO
      INTEGER*4    EM_ID
      CHARACTER*10 EM_SN
      CHARACTER*20 EM_FN
      CHARACTER*1  EM_GEN
      CHARACTER*10 EM_BD
      CHARACTER*10 EM_HD
      CHARACTER*3  EM_DP
      CHARACTER*6  EM_SL

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!   For reading attendance file    !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      ATIO
      INTEGER      ATFILE
      INTEGER*4  AT_ID
      CHARACTER*6  AT_STA
      CHARACTER*11 AT_DAT
      INTEGER    AT_HR
      INTEGER    AT_MIN 

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!           Date record            !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      CHARACTER*4    ATYEAR
      INTEGER*2    ATMONT
      CHARACTER*2    ATMSTR
      CHARACTER*2    ATDAYE
      CHARACTER*2    ATDAY
      INTEGER      ATDAYI

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! For reading monthly-attendance file !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      MAIO
      INTEGER      MAFILE
      INTEGER*4    MA_ID
      CHARACTER*3    MA_ABS
      CHARACTER*3    MALATE
      CHARACTER*3    MA_OT

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!       For summary output         !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      SMOUT
      CHARACTER*18 DATSTR
      CHARACTER*10 EMSTAT

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! For Updated monthly-attendance output !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      MAOUT

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!          For counting            !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      LOGICAL      EMARR
      LOGICAL      EMLEAV
      LOGICAL      EMLATE
      LOGICAL      DELETE

      INTEGER      EMLT
      INTEGER      EMOT
      INTEGER      EMABS

      INTEGER      RPPRES
      INTEGER      RPABS
      INTEGER      RPLATE
      INTEGER      RPSUPS

      INTEGER      LATEHR
      INTEGER      LATEMI
      INTEGER      OTHR
      INTEGER      OTMI

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!           For function           !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER      CHELAT
      INTEGER      CHEOT

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!      Variable Initialization     !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      EMFILE = 1
      ATFILE = 2
      MAFILE = 3
      SMOUT = 11
      MAOUT = 12

      RPPRES = 0
      RPABS = 0
      RPLATE = 0
      RPSUPS = 0

      EMLT = 0
      EMOT = 0
      EMABS = 0
      DELETE = .FALSE.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!      Getting file name           !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      CALL GETARG(1, FILE1)
      CALL GETARG(2, FILE2)
      CALL GETARG(3, FILE3)
!     PRINT *, "CSCI3180 ;)", FILE1,FILE2,FILE3

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!      File input and output       !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      OPEN(EMFILE, FILE = FILE1, STATUS = 'OLD')
      OPEN(ATFILE, FILE = FILE2, STATUS = 'OLD')
      OPEN(MAFILE, FILE = FILE3, STATUS = 'OLD')
      OPEN(SMOUT, FILE = 'summaryfor.txt', STATUS = 'UNKNOWN')
      OPEN(MAOUT, FILE = 'monthly-attendancefor.txt'
     $, STATUS = 'UNKNOWN')

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!         Summary heading          !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   21 FORMAT("Daily Attendance Summary\r")
   22 FORMAT("Date: ",A,"\r")
   23 FORMAT("Staff-ID Name",A28,"Department Status\r")
   24 FORMAT("-----------------------------------------"
     $,"---------------------\r")
   30 FORMAT(A4,"-",A2,"\r")
      
      WRITE(SMOUT,21)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Reading date from attendance file !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      READ(ATFILE, '(A4,A1,A2,A1,A2)') ATYEAR, JUNK, ATMSTR
     $, JUNK, ATDAYE
      READ(MAFILE,'(A)', IOSTAT = MAIO)JUNK

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!       Printing English Date      !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!     PRINT *, "Date", ATYEAR,ATMONT,ATDAY
      READ (ATDAYE,'(I2)')ATDAYI
!     PRINT *, ATDAYE, ATDAYI
      IF (ATDAYI.EQ.1) DELETE =.TRUE.
      READ(ATMSTR,'(I2)') ATMONT
      WRITE (ATDAY,'(I2)')ATDAYI
      IF (ATDAYI.LT.10)GOTO 80
      IF (ATDAYI.GE.10)GOTO 81
   80 IF (ATMONT .EQ. 1) DATSTR = "January "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 2) DATSTR = "February "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 3) DATSTR = "March "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 4) DATSTR = "April "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 5) DATSTR = "May "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 6) DATSTR = "June "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 7) DATSTR = "July "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 8) DATSTR = "August "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 9) DATSTR = "September "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 10) DATSTR = "Octorber "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 11) DATSTR = "November "//ATDAY(2:2)
     $//", "//ATYEAR
      IF (ATMONT .EQ. 12) DATSTR = "December "//ATDAY(2:2)
     $//", "//ATYEAR
!     PRINT *, ATDAYI
      GOTO 82

   81 IF (ATMONT .EQ. 1) DATSTR = "January "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 2) DATSTR = "February "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 3) DATSTR = "March "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 4) DATSTR = "April "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 5) DATSTR = "May "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 6) DATSTR = "June "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 7) DATSTR = "July "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 8) DATSTR = "August "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 9) DATSTR = "September "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 10) DATSTR = "Octorber "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 11) DATSTR = "November "//ATDAY//", "//ATYEAR
      IF (ATMONT .EQ. 12) DATSTR = "December "//ATDAY//", "//ATYEAR
      GOTO 82
!     PRINT *, "Date ", DATSTR

   82 WRITE(MAOUT,30)ATYEAR, ATMSTR
      WRITE(SMOUT,22) DATSTR
      WRITE(SMOUT,23) ""
      WRITE(SMOUT,24)
      

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!      Reading Empolyee File       !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   25 FORMAT(I4,A10,A20,A1,A10,A10,A3,A6)
   26 FORMAT(I4,XXXXX,A10,X,A20,X,A3,XXXXXXXX,A10, "\r")
   27 FORMAT(A, I4, "\r")

   50 READ(EMFILE ,25, IOSTAT = EMIO) EM_ID, EM_SN
     $, EM_FN, EM_GEN, EM_BD, EM_HD, EM_DP, EM_SL
      READ(MAFILE, 29, IOSTAT = MAIO) MA_ID, MA_ABS, MALATE, MA_OT
!     PRINT *, MA_ABS, MALATE, MA_OT
      CLOSE(ATFILE)
      IF (EMIO .LT. 0) GOTO 51
      IF (EMIO .EQ. 0) GOTO 52
      IF (EMIO .GT. 0) GOTO 99

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!    Reading Attendance for each   !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   28 FORMAT(I4,A6,A11,I2,A1,I2)
   29 FORMAT(I4,A3,A3,A3)
   33 FORMAT(I4,I3.3,I3.3,I3.3, "\r")

   52 READ(MA_ABS,'(I3)')EMABS
      READ(MALATE,'(I3)')EMLT
      READ(MA_OT,'(I3)')EMOT
      IF (DELETE) EMABS = 0
      IF (DELETE) EMLT = 0
      IF (DELETE) EMOT = 0
!     PRINT *, EMABS, EMLT, EMOT
      EMARR = .TRUE.
      EMLEAV = .TRUE.
      EMLATE = .TRUE.
      OPEN(ATFILE, FILE = FILE2, STATUS = 'OLD')
      READ(ATFILE, '(A)')JUNK

   60 READ(ATFILE, 28 , IOSTAT = ATIO) AT_ID, AT_STA
     $, AT_DAT, AT_HR, JUNK, AT_MIN
      IF (ATIO .LT. 0) GOTO 70
      IF (ATIO .EQ. 0) GOTO 61
      IF (ATIO .GT. 0) GOTO 99

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!      Finding required data       !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   61 IF(AT_ID.EQ.EM_ID .AND. AT_STA.EQ."ARRIVE" .AND. EMARR) GOTO 62
      IF(AT_ID.EQ.EM_ID .AND. AT_STA.EQ."LEAVE ".AND. EMLEAV) GOTO 63
      GOTO 60
   62 EMARR = .FALSE.
      IF(AT_HR.GE.10 .AND. AT_MIN.GE.15) EMLATE = .FALSE.
      LATEHR = AT_HR
      LATEMI = AT_MIN
      GOTO 60
   63 EMLEAV = .FALSE.
      OTHR = AT_HR
      OTMI = AT_MIN
      GOTO 60

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!         Checking status          !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   70 IF(.NOT.EMARR.AND. .NOT. EMLEAV.AND.EMLATE) GOTO 71
      IF(EMLATE .AND. EMARR .AND. EMLEAV) GOTO 72
      IF(.NOT.EMLATE.AND..NOT. EMARR .AND. .NOT. EMLEAV) GOTO 73
      EMSTAT = "SUSPICIOUS"
      WRITE(SMOUT,26)EM_ID, EM_SN, EM_FN, EM_DP , EMSTAT
      RPSUPS = RPSUPS +1
      WRITE(MAOUT,33)EM_ID, EMABS, EMLT, EMOT
      GOTO 50

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!  Print summary and update monthly-attendance  !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   71 EMSTAT = "PRESENT"
      WRITE(SMOUT,26)EM_ID, EM_SN, EM_FN, EM_DP , EMSTAT
      RPPRES = RPPRES + 1
!     PRINT *, AT_HR, AT_MIN
      IF (AT_HR.GT.17) EMOT = EMOT + CHEOT(OTHR,OTMI)
      IF (EMOT.GT.30) EMOT = 30
      WRITE(MAOUT,33)EM_ID, EMABS, EMLT, EMOT
      GOTO 50
   72 EMSTAT = "ABSENT"
      WRITE(SMOUT,26)EM_ID, EM_SN, EM_FN, EM_DP , EMSTAT
      RPABS = RPABS + 1
      EMABS = EMABS + 1
      WRITE(MAOUT,33)EM_ID, EMABS, EMLT, EMOT
      GOTO 50
   73 EMSTAT = "LATE"
      WRITE(SMOUT,26)EM_ID, EM_SN, EM_FN, EM_DP , EMSTAT
      RPLATE = RPLATE + 1
!     PRINT *,"LATE: ",LATEHR, LATEMI
      IF (AT_HR.GT.17) EMOT = EMOT + CHEOT(OTHR,OTMI)
      IF (EMOT.GT.30) EMOT = 30
      EMLT = EMLT + CHELAT(LATEHR, LATEMI)
!     PRINT *,EMLT
      WRITE(MAOUT,33)EM_ID, EMABS, EMLT, EMOT
      GOTO 50


   51 PRINT *, "DONE"
      WRITE(SMOUT,24)
      WRITE(SMOUT,27) "Number of Presences: ",RPPRES
      WRITE(SMOUT,27) "Number of Absences: ",RPABS
      WRITE(SMOUT,27) "Number of Late Arrivals: ",RPLATE
      WRITE(SMOUT,27) "Number of Suspicious Records: ",RPSUPS

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!          End of Program          !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   99 CLOSE(EMFILE)
      CLOSE(MAFILE)
      CLOSE(SMOUT)
      CLOSE(MAOUT)
      STOP
      END

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!   Function: calculate late time  !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER FUNCTION CHELAT(HR,MI)
      INTEGER    HR
      INTEGER    MI
C     HR = HR - 10
C     MI = MI + HR*60
      CHELAT = ((HR - 10)*60 + MI)/15
      END

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!   Function: calculate OT time    !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER FUNCTION CHEOT(HR,MI)
      INTEGER    HR
      INTEGER    MI
      CHEOT = HR - 17
      END
