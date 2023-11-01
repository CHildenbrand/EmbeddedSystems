
@echo Check if eclipse already imported and erase if so...
@if exist "%WORKSPACE_PATH%\.metadata" (
    @rmdir /s /q "%WORKSPACE_PATH%\.metadata"
    @if not errorlevel 0 (
       @echo Failed to delete Eclipse workspace!
       @exit 1
    ) else (
       @echo Eclipse workspace deleted!
    )
)

@echo Check if project output folder was created and erase if so...
@if exist "%PROJECT_PATH%\target" (
    @rmdir /s /q "%PROJECT_PATH%\target"
    @echo Output folder deleted!
)

@echo Import eclipse project %PROJECT_NAME% in workspace at %WORKSPACE_PATH%
%ECLIPSE% -nosplash -no-indexer -application org.eclipse.cdt.managedbuilder.core.headlessbuild -import "%PROJECT_PATH%" -data "%WORKSPACE_PATH%"

@echo Open eclipse project %PROJECT_NAME%
start %ECLIPSE% -data %WORKSPACE_PATH%