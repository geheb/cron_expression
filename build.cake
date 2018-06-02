#load "scripts/merge-source-files.cake"

var target = Argument("target", "default");
var configuration = Argument("configuration", "Release");
var solutionFile = File("./build.sln");
var buildDir = Directory("./build");
var srcDir = Directory("./src");
var testFile = File(configuration + "/cron_expression_test.exe");

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

Task("test-x86")
	.Does(() =>
{
	int exitCode = StartProcess(buildDir + Directory("test/Win32") + testFile);
	if (exitCode != 0) 
	{
		throw new Exception();
	}
});

Task("build-x64")
	.Does(() =>
{
	MSBuild(solutionFile, settings => settings
		.SetConfiguration(configuration)
		.SetPlatformTarget(PlatformTarget.x64)
		.WithTarget("Rebuild")
		.SetVerbosity(Verbosity.Minimal));
});

Task("test-x64")
	.Does(() =>
{
	int exitCode = StartProcess(buildDir + Directory("test/x64") + testFile);
	if (exitCode != 0) 
	{
		throw new Exception();
	}
});

Task("merge")
	.Does(() =>
{
	MergeSourceFilesToSingleHeaderFile(srcDir, buildDir);
});

Task("Default")
    .IsDependentOn("clean")
    .IsDependentOn("build-x86")
	.IsDependentOn("build-x64")
    .IsDependentOn("test-x86")
	.IsDependentOn("test-x64")
    .IsDependentOn("merge")
	.Does(()=> 
{ 
});
	
RunTarget(target);
