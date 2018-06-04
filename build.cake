#load "scripts/merge-source-files.cake"

var target = Argument("target", "default");
var configuration = Argument("configuration", "Release");
var solutionFile = File("./build.sln");
var buildDir = Directory("./build");
var srcDir = Directory("./src");
var testFileReporterArgs = "-r junit -s -o ";
var hasXmlReport = Argument<bool>("xmlreport", false);

Task("clean")
	.Does(() =>
{
	CleanDirectory(buildDir);
});

Task("build-x86")
	.Does(() =>
{
	MSBuild(solutionFile, settings => settings
		.SetConfiguration(configuration)
		.SetPlatformTarget(PlatformTarget.x86)
		.WithTarget("Rebuild")
		.SetVerbosity(Verbosity.Minimal));
});

Task("build-x64")
	.Does(() =>
{
	if (!Context.Environment.Platform.Is64Bit) return;
	MSBuild(solutionFile, settings => settings
		.SetConfiguration(configuration)
		.SetPlatformTarget(PlatformTarget.x64)
		.WithTarget("Rebuild")
		.SetVerbosity(Verbosity.Minimal));
});

Task("merge")
	.Does(() =>
{
	MergeSourceFilesToSingleHeaderFile(srcDir, buildDir);
});

Task("build")
	.IsDependentOn("clean")
	.IsDependentOn("build-x86")
	.IsDependentOn("build-x64")
	.IsDependentOn("merge")
	.Does(() =>
{
});

Task("test-x86")
	.Does(() =>
{
	var file = buildDir + Directory("test/Win32") + File(configuration + "/cron_expression_test.exe");
	int exitCode;
	if (!hasXmlReport)
	{
		exitCode = StartProcess(file);
	}
	else
	{
		var xmlFile = file.Path.GetDirectory().GetFilePath("testresults.xml");
		exitCode = StartProcess(file, new ProcessSettings{ Arguments = testFileReporterArgs + xmlFile});
	}
	if (exitCode != 0) 
	{
		throw new Exception("tests failed");
	}
});

Task("test-x64")
	.Does(() =>
{
	if (!Context.Environment.Platform.Is64Bit) return;
	var file = buildDir + Directory("test/x64") + File(configuration + "/cron_expression_test-x64.exe");
	int exitCode;
	if (!hasXmlReport)
	{
		exitCode = StartProcess(file);
	}
	else
	{
		var xmlFile = file.Path.GetDirectory().GetFilePath("testresults.xml");
		exitCode = StartProcess(file, new ProcessSettings{ Arguments = testFileReporterArgs + xmlFile});
	}
	if (exitCode != 0) 
	{
		throw new Exception("tests failed");
	}
});

Task("test")
	.IsDependentOn("test-x86")
	.IsDependentOn("test-x64")
	.Does(() =>
{
});

Task("Default")
    .IsDependentOn("build")
    .IsDependentOn("test")
    .IsDependentOn("merge")
	.Does(()=> 
{ 
});
	
RunTarget(target);
