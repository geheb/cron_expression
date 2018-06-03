param 
(
	[String]$XmlFile=""
)

$tests = ([xml](Get-Content $XmlFile)).testsuites.testsuite.testcase

foreach ($test in $tests) 
{
	$testName = $test.name
	$testPath = $test.classname
	$testTimeMs = ([int]([double]$test.time * 1000)) # convert to ms https://github.com/windyroad/JUnit-Schema/blob/master/JUnit.xsd
	
	$failureNode = $test.SelectSingleNode('failure')
	
	if ($failureNode) 
	{
		$errorMessage = "$($failureNode.message), $($failureNode.InnerText.Trim())"
		Add-AppveyorTest $testName -Outcome Failed -FileName $testPath -Duration $testTimeMs -ErrorMessage $errorMessage
		Add-AppveyorMessage "$testName failed" -Category Error
	}
	else 
	{
		Add-AppveyorTest $testName -Outcome Passed -FileName $testPath -Duration $testTimeMs
	}
}