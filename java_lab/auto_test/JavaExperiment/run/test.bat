@echo off
set JAVA_HOME=D:\SDK\jdk-13.0.2
set PATH=%JAVA_HOME%\bin;%PATH%

rem ��������TestNG������Jar������Ŀ¼����ǰĿ¼��lib��Ŀ¼��
set LIB_DIR=.\lib

rem ���ñ��������Ŀ¼��������Ŀ¼�ĸ�Ŀ¼��
set TO_BE_TEST_CLASSPAH=C:\Users\86156\Desktop\Experiment1Test\betest

rem ���ò������Ŀ¼(������Ŀ¼�ĸ�Ŀ¼��,Ϊ��ǰĿ¼��test\SearchEngine��Ŀ¼
set TEST_SUITE_CLASSPATH=.\test

rem ������TestNG������Jar���Ž�CLASSPATH
setlocal EnableDelayedExpansion
set DEP_JAR=""
for /r %LIB_DIR% %%i in (*.jar) do if !DEP_JAR!=="" (set DEP_JAR=%%i) else (set DEP_JAR=!DEP_JAR!;%%i) 

set CLASSPATH=%CLASSPATH%;%TO_BE_TEST_CLASSPAH%;%TEST_SUITE_CLASSPATH%;%DEP_JAR%


java  org.testng.TestNG testng.xml -d test-output