Param(
  [parameter(Mandatory=$true)]
  [ValidateNotNullOrEmpty()]
  $Version,
  
  [parameter(Mandatory=$true)]
  [ValidateNotNullOrEmpty()]
  $SourceDir,
 
  [parameter(Mandatory=$true)]
  [ValidateNotNullOrEmpty()]
  $TargetDir
)

$files = @("date_time", "cron_field", "minute_field", "hour_field", "day_of_month_field", "month_field", "day_of_week_field", "cron_expression")

$files | ForEach {
  $h = Get-Content $SourceDir/$_.h -Raw
  $cpp = Get-Content $SourceDir/$_.cpp -Raw
  $content += ($h -replace '#pragma\s*once\s*', '' -replace '\s*#\s*include\s*"(.*)"', '')
  $content += ($cpp -replace '#pragma\s*once\s*', '' -replace '\s*#\s*include\s*"(.*)"', '')
}

New-Item -ItemType Directory -Path $TargetDir -force | Out-Null

$template = (Get-Content $PSScriptRoot/file-template.txt) `
  -replace '{version}', $Version `
  -replace '{timestamp}', (Get-Date -Format o) `
  -replace '{timestamp:year}',(Get-Date).Year `
  -replace '{content}', $content

$template | Out-File $TargetDir/cron_expression.hpp -Encoding utf8 -force
